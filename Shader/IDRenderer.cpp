#include "IDRenderer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

using GeomType = float;
using ValueType = float;
using ColorType = float;

IDRenderer<GeomType, ValueType, ColorType>::Location IDRenderer<GeomType, ValueType, ColorType>::getLocations(const Crystal::Shader::ShaderObject& shader)
{
	Location location;

	location.projectionMatrix = glGetUniformLocation(shader.getId(), "projectionMatrix");
	location.modelviewMatrix = glGetUniformLocation(shader.getId(), "modelviewMatrix");

	location.position = glGetAttribLocation(shader.getId(), "position");
	location.id = glGetAttribLocation(shader.getId(), "id");

	return location;
}

void IDRenderer<GeomType, ValueType, ColorType>::render(const ICamera<GeomType>& camera)
{
	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	assert(GL_NO_ERROR == glGetError());

	glUseProgram(shader.getId());

	const Location& location = getLocations(shader);

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, &(positions.front()));
	//glVertexAttribIPointer(location.id, 1, GL_INT, 0, &(ids.front()));

	glEnableVertexAttribArray(0);

	//const auto positions = buffer.getPositions();

	glDrawArrays(GL_LINES, 0, positions.size() / 3);

	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);

}