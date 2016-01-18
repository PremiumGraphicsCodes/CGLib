#include "LegacySurfaceRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	GLfloat lightPos[] = { 1.0f, 3.0f, -5.0f, 1.0f };
	GLfloat red[] = { 1.0f, 0.4f, 0.3f, 1.0f };
	GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
}

void LegacySurfaceRenderer::render(const ICamera<float>& camera, const Surface<float>& surface, const PointLight<float>& light)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light.getPos().toArray3().data());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.getDiffuse().toArray4().data());

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
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow);
	//glColor3fv(yellow);

	for (const auto& f : surface.getFaces()) {
		glBegin(GL_TRIANGLES);
		const auto normal = f.getNormal();
		glNormal3fv(normal.toArray3().data());
		for (auto e : surface.getEdges()) {
			const auto start = e.getStartPosition();
			glVertex3d(start.getX(), start.getY(), start.getZ());
		}
		glEnd();
	};

	glDisable(GL_LIGHT0);

	glFlush();

}
