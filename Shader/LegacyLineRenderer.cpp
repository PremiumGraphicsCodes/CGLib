#include "LegacyLineRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void LegacyLineRenderer::render(const ICamera<float>& camera, const Surface<float>& surface)
{
	Matrix4d<float> projectionMatrix = camera.getProjectionMatrix();
	Matrix4d<float> modelviewMatrix = camera.getModelviewMatrix();;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projectionMatrix.toArray().data());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(modelviewMatrix.toArray().data());

	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (const auto& f : surface.getFaces()) {
		glBegin(GL_TRIANGLES);
		for (auto e : surface.getEdges()) {
			const auto start = e.getStartPosition();
			glVertex3d(start.getX(), start.getY(), start.getZ());
		}
		glEnd();
	};

	glFlush();

}
