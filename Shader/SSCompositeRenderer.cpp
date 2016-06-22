#include "stdafx.h"
#include "SSCompositeRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool SSCompositeRenderer::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string SSCompositeRenderer::getBuildinVertexShaderSource()
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
	ShaderUnit vertexShader;
	bool b = vertexShader.compile(stream.str(), ShaderUnit::Stage::VERTEX);
	return stream.str();
}

std::string SSCompositeRenderer::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform sampler2D texture1;" << std::endl
		<< "uniform sampler2D texture2;" << std::endl
		<< "uniform sampler2D depthTexture1;" << std::endl
		<< "uniform sampler2D depthTexture2;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	float depth1 = texture2D(depthTexture1, texCoord).r;" << std::endl
		<< "	float depth2 = texture2D(depthTexture2, texCoord).r;" << std::endl
		<< "	if( depth1 < depth2 ) {" << std::endl
		<< "		fragColor = texture2D(texture1, texCoord);" << std::endl
//		<< "	fragColor.rgba = vec4(1.0, 0.0, 0.0, 1.0);" << std::endl
		<< "	} else {" << std::endl
		<< "		fragColor = texture2D(texture2, texCoord);" << std::endl
//		<< "	fragColor.rgba = vec4(0.0, 0.0, 1.0, 1.0);" << std::endl
		<< "	}" << std::endl
//		<< "	fragColor.rgb = vec3(depth1);" << std::endl
		//<< "	fragColor.r = 1.0;" << std::endl
		<< "}" << std::endl;
	ShaderUnit fragmentShader;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void SSCompositeRenderer::findLocation()
{
	shader.findUniformLocation("texture1");
	shader.findUniformLocation("texture2");
	shader.findUniformLocation("depthTexture1");
	shader.findUniformLocation("depthTexture2");

	shader.findAttribLocation("position");
}

void SSCompositeRenderer::render(const ITextureObject& texture1, const ITextureObject& texture2, const DepthTextureObject& depthTexture1, const ITextureObject& depthTexture2)
{
	const Box2d<float> box(Vector2d<float>(-1.0, -1.0), Vector2d<float>(1.0, 1.0));
	const auto& positions = box.toArray();

	//glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	texture1.bind();
	texture2.bind();
	depthTexture1.bind();
	depthTexture2.bind();

	glUniform1i(shader.getUniformLocation("texture1"), texture1.getId());
	glUniform1i(shader.getUniformLocation("texture2"), texture2.getId());
	glUniform1i(shader.getUniformLocation("depthTexture1"), depthTexture1.getId());
	glUniform1i(shader.getUniformLocation("depthTexture2"), depthTexture2.getId());

	glVertexAttribPointer(shader.getAttribLocation("positions"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>( positions.size() / 2) );
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	depthTexture2.unbind();
	depthTexture1.unbind();

	texture2.unbind();
	texture1.unbind();
	//glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}