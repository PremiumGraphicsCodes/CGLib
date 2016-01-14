#include "BillBoardRenderer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;


void BillBoardRenderer<float>::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");
	shader.findUniformLocation("pointSizeX");
	shader.findUniformLocation("pointSizeY");

	shader.findUniformLocation("tex");

	shader.findAttribLocation("position");
	shader.findAttribLocation("density");
}


void BillBoardRenderer<float>::render(const ICamera<float>& camera)
{
	const auto positions = buffers[0].get();
	const auto densities = buffers[1].get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	//	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	//	glEnable(GL_POINT_SPRITE);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDepthMask(GL_FALSE);

	glUseProgram(shader.getId());

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());
	glUniform1f(shader.getUniformLocation("pointSizeX"), pointSizeX);
	glUniform1f(shader.getUniformLocation("pointSizeY"), pointSizeY);

	glUniform1i(shader.getUniformLocation("tex"), 0);

	glVertexAttribPointer(shader.getAttribLocation("positions"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("density"), 1, GL_FLOAT, GL_FALSE, 0, densities.data());
	//glVertexAttribIPointer(location.id, 1, GL_INT, 0, &(ids.front()));


	//const auto positions = buffer.getPositions();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_POINTS, 0, positions.size() / 3);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);


	glUseProgram(0);

}
