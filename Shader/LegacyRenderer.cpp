#include "stdafx.h"
#include "GLee.h"
#include "LegacyRenderer.h"

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
	glEnable(GL_DEPTH_TEST);
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

void LegacyRenderer::render(const ICamera<float>& camera, const PointIdBuffer& buffer)
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
	glColorPointer(4, GL_FLOAT, 0, colors.data());
	assert(glGetError() == GL_NO_ERROR);

	glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(positions.size()) / 3);
	//glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, indices.data());


	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

}


void LegacyRenderer::render(const ICamera<float>& camera, const LineBuffer& buffer, const GLfloat width)
{
	render(camera.getProjectionMatrix(), camera.getModelviewMatrix(), buffer, width);
}

void LegacyRenderer::render(const ICamera<float>& camera, const Line2dBuffer& buffer, const GLfloat width)
{
	render(camera.getProjectionMatrix(), camera.getModelviewMatrix(), buffer, width);
}


void LegacyRenderer::render(const LineBuffer& buffer, const GLfloat width)
{
	render(Matrix4d<float>::Identity(), Matrix4d<float>::Identity(), buffer, width);
}

void LegacyRenderer::render(const Matrix4d<float>& projectionMatrix, const Matrix4d<float>& modelviewMatrix, const LineBuffer& buffer, const GLfloat width)
{
	const auto& positions = buffer.getPosition().get();// buffers[0].get();
	const auto& colors = buffer.getColor().get();
	const auto& indices = buffer.getIds();

	if (positions.empty()) {
		return;
	}

	glLineWidth(width);
	glEnable(GL_DEPTH_TEST);

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
	glDrawElements(GL_LINES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_DEPTH_TEST);

	glLineWidth(1);
}

void LegacyRenderer::render(const Matrix4d<float>& projectionMatrix, const Matrix4d<float>& modelviewMatrix, const Line2dBuffer& buffer, const GLfloat width)
{
	const auto& positions = buffer.getPosition().get();// buffers[0].get();
	const auto& colors = buffer.getColor().get();
	const auto& indices = buffer.getIds();

	if (positions.empty()) {
		return;
	}

	glLineWidth(width);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projectionMatrix.toArray().data());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(modelviewMatrix.toArray().data());

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, positions.data());

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colors.data());
	assert(glGetError() == GL_NO_ERROR);

	//glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(positions.size()) / 3);
	glDrawElements(GL_LINES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_DEPTH_TEST);

	glLineWidth(1);
}


void LegacyRenderer::renderId(const ICamera<float>& camera, const LineIdBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();// buffers[0].get();
	const auto& colors = buffer.getIds().get();
	const auto& indices = buffer.getIndices();

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
	glDrawElements(GL_LINES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());


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
	const auto& positions = buffer.getPositions().get();// buffers[0].get();
	const auto& normals = buffer.getNormals().get();//buffers[1].get();

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
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light.getSpecular().toArray4().data());
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projectionMatrix.toArray().data());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(modelviewMatrix.toArray().data());


	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, positions.data());

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals.data());

	//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size()) / 3);
	for (const auto& b : buffer.getBlocks()) {
		const auto& indices = b.getIndices();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);

}

/*
void LegacyRenderer::render(const ICamera<float>& camera, const TriangleIdBuffer& buffer)
{
	const auto& positions = buffer.getPositions().get();// buffers[0].get();
	const auto& indices = buffer.getIndices();
	const auto& colors = buffer.getIdColors().get();

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
*/