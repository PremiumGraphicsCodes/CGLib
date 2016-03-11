#include "GLee.h"

#include "LegacyRenderer.h"

#include "../Math/Vector3d.h"
#include "../Math/Matrix4d.h"
#include "../Graphics/ICamera.h"
#include "../Graphics/Light.h"
#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void LegacyRenderer::render(const ICamera<float>& camera, const PointBuffer& buffer, const float pointSize)
{
	const auto& positions = buffer.getPosition().get();// buffers[0].get();
	const auto& colors = buffer.getColor().get();

	if (positions.empty()) {
		return;
	}

	GLfloat distance[] = { 0.0, 0.0, 1.0 };
	glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);

	glEnable(GL_POINT_SPRITE);
	glDisable(GL_DEPTH_TEST);
	glPointSize(pointSize);

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

	glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(positions.size()) / 3);
	//glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, indices.data());


	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_POINT_SPRITE);


}

void LegacyRenderer::renderId(const ICamera<float>& camera, const PointBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();// buffers[0].get();
	const auto& colors = buffer.getIdColor().get();

	if (positions.empty()) {
		return;
	}

	glDisable(GL_DEPTH_TEST);
	glPointSize(10.0f);

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
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors.data());
	assert(glGetError() == GL_NO_ERROR);

	glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(positions.size()) / 3);
	//glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, indices.data());


	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_DEPTH_TEST);

}


void LegacyRenderer::renderAlphaBlend(const ICamera<float>& camera, const PointBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();// buffers[0].get();
	const auto& colors = buffer.getColor().get();

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
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors.data());
	assert(glGetError() == GL_NO_ERROR);

	glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(positions.size()) / 3);
	//glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, indices.data());


	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

}


void LegacyRenderer::render(const ICamera<float>& camera, const LineBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();// buffers[0].get();
	const auto& colors = buffer.getColor().get();
	const auto& indices = buffer.getIds();

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

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, positions.data());

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colors.data());
	assert(glGetError() == GL_NO_ERROR);

	//glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(positions.size()) / 3);
	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, indices.data());


	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_DEPTH_TEST);

}

void LegacyRenderer::renderId(const ICamera<float>& camera, const LineBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();// buffers[0].get();
	const auto& colors = buffer.getIdColors().get();
	const auto& indices = buffer.getIds();

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

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, positions.data());

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colors.data());
	assert(glGetError() == GL_NO_ERROR);

	//glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(positions.size()) / 3);
	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, indices.data());


	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_DEPTH_TEST);

}


namespace {
	GLfloat yellow[] = { 0.0, 1.0, 1.0, 1.0 };
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
}

void LegacyRenderer::render(const ICamera<float>& camera, const PointLight<float>& light, const TriangleBuffer& buffer)
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
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.getSpecular().toArray4().data());

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

void LegacyRenderer::renderId(const ICamera<float>& camera, const TriangleBuffer& buffer)
{
	const auto& positions = buffer.positions.get();// buffers[0].get();
	const auto& indices = buffer.indices;
	const auto& colors = buffer.colors.get();


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

	assert(GL_NO_ERROR == glGetError());


	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, positions.data());

	assert(GL_NO_ERROR == glGetError());


	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors.data());

	assert(GL_NO_ERROR == glGetError());

	//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size()) / 3);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_DEPTH_TEST);

}
