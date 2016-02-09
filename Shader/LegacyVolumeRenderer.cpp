#include "LegacyVolumeRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void LegacyVolumeRenderer::render(ICamera<float>& camera, const PointBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();// buffers[0].get();
	const auto& colors = buffer.getColor().get();
	const auto& indices = buffer.getIds();

	if (positions.empty()) {
		return;
	}

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glPointSize(10.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Matrix4d<float> projectionMatrix = camera.getProjectionMatrix();
	Matrix4d<float> modelviewMatrix = camera.getModelviewMatrix();;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projectionMatrix.toArray().data());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(modelviewMatrix.toArray().data());

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, positions.data());

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colors.data());
	assert(glGetError() == GL_NO_ERROR);

	//glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(positions.size()) / 3);
	glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, indices.data());


	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

}