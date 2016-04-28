#include "BilateralFilter.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool BilateralFilter::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string BilateralFilter::getBuildinVertexShaderSource()
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

std::string BilateralFilter::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform sampler2D tex;" << std::endl
		<< "uniform float width;" << std::endl
		<< "uniform float height;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	float sum = 0;" << std::endl
		<< "	float wsum = 0;" << std::endl
		<< "	float filterRadius = 5;" << std::endl
		<< "	float blurScale = 1;" << std::endl
		<< "	float blurDepthFalloff = 1.0;" << std::endl
		<< "	float depth = texture2D(tex, texCoord).r;" << std::endl
		<< "	for(float x = -filterRadius; x <= filterRadius; x+= 1.0){" << std::endl
		<< "		for(float y = -filterRadius; y <= filterRadius; y+= 1.0){" << std::endl
		<< "			float dxx = (x/width);" << std::endl
		<< "			float dyy = (y/height);" << std::endl
		<< "			vec2 offset = vec2(dxx,dyy);" << std::endl
		<< "			float sample = texture2D(tex, texCoord + offset ).r;" << std::endl
		<< "			float r = sqrt(dxx * dxx + dyy * dyy) * blurScale;" << std::endl
		<< "			float w = exp(-r*r);" << std::endl
		<< "			float r2 = (sample-depth) * blurDepthFalloff;" << std::endl
		<< "			float g = exp(-r2*r2);" << std::endl
		<< "			sum += sample * w * g;" << std::endl
		<< "			wsum += w * g;" << std::endl
		<< "		}" << std::endl
		<< "	}" << std::endl
		<< "	if(wsum > 0.0) {" << std::endl
		<< "		sum /= wsum;" << std::endl
		<< "	}" << std::endl
		<< "	fragColor = vec4(sum);" << std::endl
		<< "}" << std::endl;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void BilateralFilter::findLocation()
{
	shader.findAttribLocation("position");
	shader.findUniformLocation("tex");
	shader.findUniformLocation("width");
	shader.findUniformLocation("height");
}

#include "../Graphics/OrthogonalCamera.h"
#include "../Math/Box2d.h"

void BilateralFilter::render(const ITexture& texture)
{
	const Box2d<float> box(Vector2d<float>(-1.0f, -1.0f), Vector2d<float>(1.0f, 1.0f));
	const auto& positions = box.toArray();


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	glVertexAttribPointer(shader.getAttribLocation("position"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

	texture.bind();
	glUniform1i(shader.getUniformLocation("tex"), texture.getId());
	glUniform1f(shader.getUniformLocation("width"), texture.getWidth());
	glUniform1f(shader.getUniformLocation("height"), texture.getHeight());

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_QUADS, 0, positions.size() / 2);

	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	texture.unbind();

	glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}