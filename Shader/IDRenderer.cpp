#include "IDRenderer.h"
#include "ShaderHandler.h"
#include "../Graphics/PointIdBuffer.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	std::string shaderName = "id";
}


bool IDRenderer::build()
{
	const auto& vShader = getBuildinVertexShaderSource();
	const auto& fShader = getBuildinFragmentShaderSource();

	bool result = ShaderHandler::getInstance()->build(shaderName, vShader, fShader);
	set(ShaderHandler::getInstance()->get(shaderName));

	return result;
}

std::string IDRenderer::getBuildinVertexShaderSource() const
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

std::string IDRenderer::getBuildinFragmentShaderSource() const
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


void IDRenderer::set(ShaderObject* shader)
{
	this->shader = shader;
	location.projectionMatrix = glGetUniformLocation(shader->getId(), "projectionMatrix");
	location.modelviewMatrix = glGetUniformLocation(shader->getId(), "modelviewMatrix");

	location.position = glGetAttribLocation(shader->getId(), "position");
	location.id = glGetAttribLocation(shader->getId(), "id");
}

void IDRenderer::render(const ICamera<float>& camera, const PointIdBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();
	const auto& ids = buffer.getIdColor().get();
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

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(location.id, 4, GL_FLOAT, GL_FALSE, 0, ids.data());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//const auto positions = buffer.getPositions();

	//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>( positions.size() / 3));

	glDrawArrays(GL_POINTS, 0, positions.size() / 3);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader->getId(), 0, "fragColor");

	glUseProgram(0);

	glDisable(GL_DEPTH_TEST);


	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);
}

void IDRenderer::render(const ICamera<float>& camera, const LineIdBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();
	const auto& ids = buffer.getIdColors().get();
	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	assert(GL_NO_ERROR == glGetError());

	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader->getId());

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(location.id, 4, GL_FLOAT, GL_FALSE, 0, ids.data());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//const auto positions = buffer.getPositions();

	glDrawArrays(GL_LINES, 0, static_cast<GLsizei>( positions.size() / 3));
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());


	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader->getId(), 0, "fragColor");

	glUseProgram(0);

	glDisable(GL_DEPTH_TEST);
}

void IDRenderer::render(const ICamera<float>& camera, const TriangleIdBuffer& buffer)
{
	const auto& indices = buffer.getIndices();
	const auto& positions = buffer.getPositions().get();
	const auto& ids = buffer.getIdColors().get();
	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	assert(GL_NO_ERROR == glGetError());

	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader->getId());

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(location.id, 4, GL_FLOAT, GL_FALSE, 0, ids.data());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//const auto positions = buffer.getPositions();

	//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>( positions.size() / 3));
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());


	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader->getId(), 0, "fragColor");

	glUseProgram(0);

	glDisable(GL_DEPTH_TEST);
}