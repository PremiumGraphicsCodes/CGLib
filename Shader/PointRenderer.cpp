#include "PointRenderer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void PointRenderer<float>::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");

	shader.findAttribLocation("position");
	shader.findAttribLocation("color");
	shader.findAttribLocation("pointSize");
}


void PointRenderer<float>::render(const ICamera<float>& camera, const PointBuffer& buffer)
{
	const auto positions = buffer.getPosition().get();
	const auto colors = buffer.getColor().get();
	const auto sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	glEnable(GL_DEPTH_TEST);


	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDepthMask(GL_FALSE);
	//glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(shader.getAttribLocation("positions"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("color"), 4, GL_FLOAT, GL_FALSE, 0, colors.data());
	glVertexAttribPointer(shader.getAttribLocation("pointSize"), 1, GL_FLOAT, GL_FALSE, 0, sizes.data());


	//const auto positions = buffer.getPositions();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_POINTS, 0, positions.size() / 3);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);


	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);

	glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}
