#include "LegacyLineRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void LegacyLineRenderer::render(const ICamera<float>& camera, const Surface<float>& surface, const LineBuffer& buffer)
{
	const auto& positions = buffer.getBuffers()[0].get();// buffers[0].get();

	if (positions.empty()) {
		return;
	}

	glEnable(GL_DEPTH_TEST);

	Matrix4d<float> projectionMatrix = camera.getProjectionMatrix();
	Matrix4d<float> modelviewMatrix = camera.getModelviewMatrix();;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projectionMatrix.toArray().data());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(modelviewMatrix.toArray().data());

	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, positions.data());
	assert(glGetError() == GL_NO_ERROR);

	glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(positions.size()) / 3);

	glDisableClientState(GL_VERTEX_ARRAY);

	glFlush();

}
