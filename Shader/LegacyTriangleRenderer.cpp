#include "LegacyTriangleRenderer.h"
#include "../Graphics/Buffer4d.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	GLfloat yellow[] = { 0.0, 1.0, 1.0, 1.0 };
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
}

void LegacyTriangleRenderer::render(const ICamera<float>& camera, const PointLight<float>& light, const TriangleBuffer& buffer)
{
	const auto& positions = buffer.positions.get();// buffers[0].get();
	const auto& normals = buffer.normals.get();//buffers[1].get();
	const auto& indices = buffer.indices;

	if (positions.empty()) {
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelviewMatrix();;

	std::vector<float> lightPos = { light.getPos().getX(), light.getPos().getY(), light.getPos().getZ(), 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos.data());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.getDiffuse().toArray4().data());


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projectionMatrix.toArray().data());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(modelviewMatrix.toArray().data());

	//glLightfv(GL_LIGHT0, GL_AMBIENT, white);

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, positions.data());

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals.data());

	//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size()) / 3);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);

}

namespace {
	ColorRGBA<float> toColor(const unsigned int id) {
		const auto r = id / 255.0;
		const auto g = 0.0;
		const auto b = 0.0;
		return ColorRGBA<float>(r, g, b, 1.0);
	}
}

void LegacyTriangleRenderer::renderId(const ICamera<float>& camera, const TriangleBuffer& buffer)
{
	const auto& positions = buffer.positions.get();// buffers[0].get();
	const auto& indices = buffer.indices;
	std::vector<ColorRGBA<float>> colors;
	Buffer4d<float> colorBuffer;
	for (auto i : buffer.indices) {
		colorBuffer.add( toColor(i) );
	}

	if (positions.empty()) {
		return;
	}

	glEnable(GL_DEPTH_TEST);

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelviewMatrix();;


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projectionMatrix.toArray().data());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(modelviewMatrix.toArray().data());


	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, positions.data());

	glEnableClientState(GL_COLOR_ARRAY);
	glNormalPointer(GL_FLOAT, 0, colors.data());

	//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size()) / 3);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glDisable(GL_DEPTH_TEST);

}