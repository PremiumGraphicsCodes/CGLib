#include "SSNormalRenderer.h"
#include "../Math/Box2d.h"
#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void SSNormalRenderer::build(const int width, const int height)
{
	const auto vsSource = getBuiltinVertexShaderSource();
	const auto fsSource = getBuiltinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
}

void SSNormalRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");

	shader.findAttribLocation("position");
	shader.findAttribLocation("normal");
}

std::string SSNormalRenderer::getBuiltinVertexShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec3 normal;" << std::endl
		<< "out vec4 vPosition;" << std::endl
		<< "out vec3 vNormal;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	vPosition = gl_Position;" << std::endl
		<< "	vNormal = normal;" << std::endl
		<< "}" << std::endl;
	ShaderUnit vertexShader;
	bool b = vertexShader.compile(stream.str(), ShaderUnit::Stage::VERTEX);
	return stream.str();
}

std::string SSNormalRenderer::getBuiltinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec4 vPosition;" << std::endl
		<< "in vec3 vNormal;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	fragColor.rgb = vNormal;" << std::endl
		<< "}" << std::endl;
	ShaderUnit fragmentShader;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void SSNormalRenderer::render(const int width, const int height, const ICamera<float>& camera, const TriangleBuffer& buffer)
{
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();
	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& indices = buffer.getIndices();
	const auto& positions = buffer.getPositions().get();
	const auto& normals = buffer.getNormals().get();

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	glUseProgram(shader.getId());

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("normal"), 3, GL_FLOAT, GL_FALSE, 0, normals.data());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
	glEnableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);
}
