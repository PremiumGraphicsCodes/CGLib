#include "stdafx.h"
#include "PointIDRenderer.h"

#include "ShaderHandler.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	std::string shaderName = "pointid";
}

bool PointIdRenderer::build()
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

std::string PointIdRenderer::getBuildinVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec4 id;" << std::endl
		<< "in float pointSize;" << std::endl
		<< "out vec4 vId;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "void main(void)" << std::endl
		<< "{" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	gl_PointSize = pointSize / gl_Position.w;" << std::endl
		<< "	vId = id;" << std::endl
		<< "}";
	return stream.str();
}

std::string PointIdRenderer::getBuildinFragmentShaderSource() const
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


void PointIdRenderer::set(ShaderObject* shader)
{
	this->shader = shader;

	shader->findUniformLocation("projectionMatrix");
	shader->findUniformLocation("modelviewMatrix");
	
	shader->findAttribLocation("position");
	shader->findAttribLocation("id");
	shader->findAttribLocation("pointSize");
}

void PointIdRenderer::render(const ICamera<float>& camera, const PointIdBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();
	const auto& ids = buffer.getIdColor().get();
	const auto& sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	assert(GL_NO_ERROR == glGetError());

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);


	glUseProgram(shader->getId());

	glUniformMatrix4fv(shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader->getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(shader->getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader->getAttribLocation("id"), 4, GL_FLOAT, GL_FALSE, 0, ids.data());
	glVertexAttribPointer(shader->getAttribLocation("pointSize"), 1, GL_FLOAT, GL_FALSE, 0, sizes.data());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>( positions.size() / 3) );

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader->getId(), 0, "fragColor");

	glUseProgram(0);

	glDisable(GL_DEPTH_TEST);


	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);
}
