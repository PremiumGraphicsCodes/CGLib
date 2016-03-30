#include "LineRenderer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void LineRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");
	shader.findAttribLocation("position");
	shader.findAttribLocation("color");
}

void LineRenderer::render(const ICamera<float>& camera)
{
	const auto positions = buffers[0].get();
	const auto colors = buffers[1].get();
	if (positions.empty()) {
		return;
	}

	glEnable(GL_DEPTH_TEST);

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	glUseProgram(shader.getId());
	//shader.findAttribLocation("id");

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("color"), 4, GL_FLOAT, GL_FALSE, 0, colors.data());
	//glVertexAttribIPointer(location.id, 1, GL_INT, 0, &(ids.front()));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//const auto positions = buffer.getPositions();

	glDrawArrays(GL_LINES, 0, static_cast<int>(positions.size()) / 3);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);

	glDisable(GL_DEPTH_TEST);
}
