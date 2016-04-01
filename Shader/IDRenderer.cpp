#include "IDRenderer.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool IDRenderer::build()
{
	const auto& vShader = getBuildinVertexShaderSource();
	const auto& fShader = getBuildinFragmentShaderSource();
	bool b = shader.build(vShader, fShader);
	findLocation();
	return b;
}

std::string IDRenderer::getBuildinVertexShaderSource() const
{
	std::ostringstream stream;
	stream << "#version 150" << std::endl;
	stream << "in vec3 position;" << std::endl;
	stream << "in vec4 id;" << std::endl;
	stream << "out vec4 vId;" << std::endl;
	stream << "uniform mat4 projectionMatrix;" << std::endl;
	stream << "uniform mat4 modelviewMatrix;" << std::endl;
	stream << "void main(void)" << std::endl;
	stream << "{" << std::endl;
	stream << "gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl;
	stream << "vId = id;" << std::endl;
	stream << "}";
	return stream.str();
}

std::string IDRenderer::getBuildinFragmentShaderSource() const
{
	std::ostringstream stream;
	stream << "#version 150" << std::endl;
	stream << "in vec4 vId;" << std::endl;
	stream << "out vec4 fragColor;" << std::endl;
	stream << "void main(void) {" << std::endl;
	stream << "fragColor = vId;" << std::endl;
	stream << "}" << std::endl;
	return stream.str();
}


void IDRenderer::findLocation()
{
	location.projectionMatrix = glGetUniformLocation(shader.getId(), "projectionMatrix");
	location.modelviewMatrix = glGetUniformLocation(shader.getId(), "modelviewMatrix");

	location.position = glGetAttribLocation(shader.getId(), "position");
	location.id = glGetAttribLocation(shader.getId(), "id");
}

void IDRenderer::render(const ICamera<float>& camera, const PointBuffer& buffer)
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


	glUseProgram(shader.getId());

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

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);

	glDisable(GL_DEPTH_TEST);


	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);
}


void IDRenderer::render(const ICamera<float>& camera, const TriangleBuffer& buffer)
{
	const auto& indices = buffer.indices;
	const auto& positions = buffer.positions.get();
	const auto& ids = buffer.idColors.get();
	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	assert(GL_NO_ERROR == glGetError());

	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

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

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);

	glDisable(GL_DEPTH_TEST);


}