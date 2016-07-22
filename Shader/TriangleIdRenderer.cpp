#include "stdafx.h"
#include "TriangleIDRenderer.h"

#include "ShaderHandler.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	std::string shaderName = "triangleid";
}

bool TriangleIdRenderer::build()
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

std::string TriangleIdRenderer::getBuildinVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "void main(void)" << std::endl
		<< "{" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "}";
	return stream.str();
}

std::string TriangleIdRenderer::getBuildinFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform vec4 idColor;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	fragColor = idColor;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}


void TriangleIdRenderer::set(ShaderObject* shader)
{
	this->shader = shader;

	shader->findUniformLocation("projectionMatrix");
	shader->findUniformLocation("modelviewMatrix");
	shader->findUniformLocation("idColor");

	shader->findAttribLocation("position");
}

void TriangleIdRenderer::render(const ICamera<float>& camera, const TriangleIdBuffer& buffer)
{
	const auto& blocks = buffer.getBlocks();
	const auto& positions = buffer.getPositions().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	assert(GL_NO_ERROR == glGetError());

	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader->getId());

	glUniformMatrix4fv(shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader->getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(shader->getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());

	glEnableVertexAttribArray(0);

	for (const auto& block : blocks) {
		const auto& indices = block.indices;
		auto idColor = block.idColor.get();
		glUniform4fv(shader->getUniformLocation("idColor"), 1, idColor.data());
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>( indices.size() ), GL_UNSIGNED_INT, indices.data());
	}

	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader->getId(), 0, "fragColor");

	glUseProgram(0);

	glDisable(GL_DEPTH_TEST);

}
