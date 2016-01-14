#include "QuadRenderer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

using GeomType = float;

void QuadRenderer<GeomType>::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");
	shader.findAttribLocation("position");
	shader.findAttribLocation("color");
	shader.findAttribLocation("texCoord");
}

void QuadRenderer<GeomType>::render(const ICamera<GeomType>& camera)
{
	const auto& positions = buffers[0].get();
	const auto& colors = buffers[1].get();
	const auto& texCoords = buffers[2].get();
	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	glUseProgram(shader.getId());
	//shader.findAttribLocation("id");

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("color"), 4, GL_FLOAT, GL_FALSE, 0, colors.data());
	glVertexAttribPointer(shader.getAttribLocation("texCoord"), 2, GL_FLOAT, GL_FALSE, 0, texCoords.data());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//const auto positions = buffer.getPositions();

	glDrawArrays(GL_QUADS, 0, static_cast<int>(positions.size()) / 3);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);

}

template class QuadRenderer<float>;