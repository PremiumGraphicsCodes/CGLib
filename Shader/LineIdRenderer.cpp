#include "stdafx.h"
#include "LineIdRenderer.h"

#include "ShaderHandler.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	std::string shaderName = "lineid";
}

bool LineIdRenderer::build()
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

std::string LineIdRenderer::getBuildinVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec4 id;" << std::endl
		<< "out vec4 vId;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "void main(void)" << std::endl
		<< "{" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	vId = id;" << std::endl
		<< "}";
	return stream.str();
}

std::string LineIdRenderer::getBuildinFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec4 vId;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	fragColor = vId;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}


void LineIdRenderer::set(ShaderObject* shader)
{
	this->shader = shader;

	shader->findUniformLocation("projectionMatrix");
	shader->findUniformLocation("modelviewMatrix");

	shader->findAttribLocation("position");
	shader->findAttribLocation("id");
}

void LineIdRenderer::render(const ICamera<float>& camera, const LineIdBuffer& buffer, const float width)
{
	const auto& indices = buffer.getIndices();
	const auto& positions = buffer.getPosition().get();
	const auto& ids = buffer.getIds().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	assert(GL_NO_ERROR == glGetError());

	glEnable(GL_DEPTH_TEST);
	glLineWidth(width);


	glUseProgram(shader->getId());

	glUniformMatrix4fv(shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader->getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(shader->getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader->getAttribLocation("id"), 4, GL_FLOAT, GL_FALSE, 0, ids.data());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawElements(GL_LINES, static_cast<GLsizei>( indices.size() ), GL_UNSIGNED_INT, indices.data());

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader->getId(), 0, "fragColor");

	glUseProgram(0);

	glLineWidth(1);

	glDisable(GL_DEPTH_TEST);

}
