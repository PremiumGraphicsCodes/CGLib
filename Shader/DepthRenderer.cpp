#include "stdafx.h"
#include "DepthRenderer.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool DepthRenderer::build()
{
	const auto vsSource = getBuiltinVertexShaderSource();
	const auto fsSource = getBuiltinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string DepthRenderer::getBuiltinVertexShaderSource()
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
	return stream.str();
}

std::string DepthRenderer::getBuiltinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform sampler2D depthTexture;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	fragColor = texture2D(depthTexture, texCoord);" << std::endl
		<< "	fragColor.a = 1.0; " << std::endl
		<< "	gl_FragDepth = fragColor.a; " << std::endl
		<< "}" << std::endl;
	return stream.str();
}

void DepthRenderer::findLocation()
{
	shader.findUniformLocation("depthTexture");
	shader.findAttribLocation("position");
}

void DepthRenderer::render(const DepthTextureObject& depthTexture)
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

	glUseProgram(shader.getId());

	depthTexture.bind();

	glUniform1i(shader.getUniformLocation("depthTexture"), depthTexture.getId());
	glVertexAttribPointer(shader.getAttribLocation("positions"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, positions.size() / 2);
	glDisableVertexAttribArray(0);
	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	depthTexture.unbind();

	glUseProgram(0);

}