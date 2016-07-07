#include "stdafx.h"
#include "TriangleRenderer.h"
#include <sstream>

#include "ShaderHandler.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	std::string shaderName = "triangle";
}

bool TriangleRenderer::build()
{
	const auto& vShader = getBuildinVertexShaderSource();
	const auto& fShader = getBuildinFragmentShaderSource();

	bool result = ShaderHandler::getInstance()->build(shaderName, vShader, fShader);
	if (result) {
		set(ShaderHandler::getInstance()->get(shaderName));
	}
	this->shader = ShaderHandler::getInstance()->get(shaderName);

	return result;
}

std::string TriangleRenderer::getBuildinVertexShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec4 color;" << std::endl
		<< "out vec4 vColor;" << std::endl
		<< "uniform mat4 projectionMatrix;"
		<< "uniform mat4 modelviewMatrix;"
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	vColor = color;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string TriangleRenderer::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec4 vColor;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	fragColor = vColor;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}


void TriangleRenderer::set(ShaderObject* shader)
{
	this->shader = shader;
	shader->findUniformLocation("projectionMatrix");
	shader->findUniformLocation("modelviewMatrix");

	shader->findAttribLocation("position");
	shader->findAttribLocation("color");
}


void TriangleRenderer::render(const ICamera<float>& camera, const TriangleColorBuffer& buffer)
{
	const auto& indices = buffer.getIndices();
	const auto& positions = buffer.getPositions().get();// buffers[0].get();
	const auto& colors = buffer.getColors().get();//buffers[1].get();
	if (positions.empty()) {
		return;
	}

	glEnable(GL_DEPTH_TEST);

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	assert(GL_NO_ERROR == glGetError());

	glUseProgram(shader->getId());


	glBindFragDataLocation(shader->getId(), 0, "fragColor");

	glUniformMatrix4fv(shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader->getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	assert(GL_NO_ERROR == glGetError());

	glVertexAttribPointer(shader->getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader->getAttribLocation("color"), 4, GL_FLOAT, GL_FALSE, 0, colors.data());
	//glVertexAttribPointer(location.)
	assert(GL_NO_ERROR == glGetError());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	assert(GL_NO_ERROR == glGetError());

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	glUseProgram(0);

	glDisable(GL_DEPTH_TEST);
}
