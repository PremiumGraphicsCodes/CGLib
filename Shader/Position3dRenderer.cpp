#include "stdafx.h"
#include "Position3dRenderer.h"
#include "../Math/Box2d.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool Position3dRenderer::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string Position3dRenderer::getBuildinVertexShaderSource()
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

std::string Position3dRenderer::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform sampler2D depthTex;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "float getDepth(vec2 tCoord){" << std::endl
		<< "	return texture2D(depthTex, tCoord).r;" << std::endl
		<< "}" << std::endl
		<< "vec3 uvToEye(vec2 tCoord, float depth) {" << std::endl
		<< "	vec4 clippingPosition = vec4(tCoord, depth, 1.0);" << std::endl
		<< "	vec4 viewPosition = inverse(projectionMatrix) * clippingPosition;" << std::endl
		<< "    return viewPosition.xyz / viewPosition.w;" << std::endl
		<< "}" << std::endl
		<< "vec3 getEyePosition(vec2 texCoord){"
		<< "	float depth = getDepth(texCoord);" << std::endl
		<< "	return uvToEye(texCoord, depth);" << std::endl
		<< "}" << std::endl
		<< "void main(void) {" << std::endl
		<< "	float depth = getDepth(texCoord);" << std::endl
		<< "	if(depth < 0.01) {" << std::endl
		<< "		fragColor = vec4(0.0, 0.0, 0.0, 0.0);" << std::endl
		<< "		return;" << std::endl
		<< "	}" << std::endl
		<< "    vec3 eyePosition = getEyePosition(texCoord);" << std::endl
		<< "	fragColor.rgb = eyePosition;" << std::endl
		<< "	fragColor.a = 1.0;" << std::endl
		<< "	}" << std::endl;
	ShaderUnit fragmentShader;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void Position3dRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("depthTex");
	shader.findAttribLocation("position");
}

void Position3dRenderer::render(const ITextureObject& depthTexture, const ICamera<float>& renderedCamera)
{
	const Box2d<float> box(Vector2d<float>(-1.0, -1.0), Vector2d<float>(1.0, 1.0));
	const auto& positions = box.toArray();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);
	assert(GL_NO_ERROR == glGetError());

	glUseProgram(shader.getId());
	assert(GL_NO_ERROR == glGetError());

	depthTexture.bind();
	assert(GL_NO_ERROR == glGetError());

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, renderedCamera.getProjectionMatrix().toArray().data());
	assert(GL_NO_ERROR == glGetError());

	glUniform1i(shader.getUniformLocation("depthTex"), depthTexture.getId());

	glVertexAttribPointer(shader.getAttribLocation("positions"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());
	assert(GL_NO_ERROR == glGetError());


	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, positions.size() / 2);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	depthTexture.unbind();
	glDisable(GL_DEPTH_TEST);

	assert(GL_NO_ERROR == glGetError());

	glUseProgram(0);
}