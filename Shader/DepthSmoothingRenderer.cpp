#include "stdafx.h"
#include "DepthSmoothingRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool DepthSmoothingRenderer::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string DepthSmoothingRenderer::getBuildinVertexShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec2 position;" << std::endl
		<< "out vec2 texCoord;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	texCoord = (position + vec2(1.0,1.0))/2.0;" << std::endl
		<< "	gl_Position = vec4(position, 0.0, 1.0);" << std::endl
		<< "}" << std::endl;
	bool b = vertexShader.compile(stream.str(), ShaderUnit::Stage::VERTEX);
	return stream.str();
}

std::string DepthSmoothingRenderer::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform sampler2D tex;" << std::endl
		<< "uniform int isX;" << std::endl
		<< "uniform float width;" << std::endl
		<< "uniform float height;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	float sum = 0;" << std::endl
		<< "	float wsum = 0;" << std::endl
		<< "	float filterRadius = 5;" << std::endl
		<< "	float blurScale = 1;" << std::endl
		<< "	float blurDepthFalloff = 1.0;" << std::endl
		<< "	float depth = texture2D(tex, texCoord).r;" << std::endl
		<< "	for(float x = -filterRadius; x <= filterRadius; x+= 1.0){" << std::endl
		<< "		float dx = (isX == 1) ? (x/width) : (x/height); " << std::endl
		<< "		vec2 offset = (isX == 1) ? vec2(dx,0) : vec2(0,dx);" << std::endl
		<< "		float sample = texture2D(tex, texCoord + offset ).r;" << std::endl
		<< "		float r = dx * blurScale;" << std::endl
		<< "		float w = exp(-r*r);" << std::endl
		<< "		float r2 = (sample-depth) * blurDepthFalloff;" << std::endl
		<< "		float g = exp(-r2*r2);" << std::endl
		<< "		sum += sample * w * g;" << std::endl
		<< "		wsum += w * g;" << std::endl
		<< "	}" << std::endl
		<< "	if(wsum > 0.0) {" << std::endl
		<< "		sum /= wsum;" << std::endl
		<< "	}" << std::endl
		<< "	gl_FragDepth = sum;" << std::endl
		<< "}" << std::endl;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void DepthSmoothingRenderer::findLocation()
{
	shader.findAttribLocation("position");
	shader.findUniformLocation("tex");
	shader.findUniformLocation("width");
	shader.findUniformLocation("height");
	shader.findUniformLocation("isX");
}

void DepthSmoothingRenderer::render(const ITextureObject& texture, bool isX)
{
	std::vector<float> positions;
	positions.push_back(-1.0f);
	positions.push_back(1.0f);
	positions.push_back(-1.0f);
	positions.push_back(-1.0f);
	positions.push_back(1.0f);
	positions.push_back(-1.0f);
	positions.push_back(1.0f);
	positions.push_back(1.0f);

	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	glVertexAttribPointer(shader.getAttribLocation("position"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

	texture.bind();
	glUniform1i(shader.getUniformLocation("isX"), int(isX));
	glUniform1i(shader.getUniformLocation("tex"), texture.getId());
	glUniform1f(shader.getUniformLocation("width"), texture.getWidth() * 1.0f);
	glUniform1f(shader.getUniformLocation("height"), texture.getHeight() * 1.0f);

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>( positions.size() / 2 ));

	glDisableVertexAttribArray(0);

	texture.unbind();

	glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}