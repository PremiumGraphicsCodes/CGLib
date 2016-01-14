#include "SmoothRenderer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void SmoothRenderer<float>::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");
	shader.findUniformLocation("eyePosition");

	shader.findAttribLocation("position");
	shader.findAttribLocation("normal");
}


void SmoothRenderer<float>::render(const ICamera<float>& camera)
{
	const auto& positions = buffer.positions.get();// buffers[0].get();
	const auto& normals = buffer.normals.get();//buffers[1].get();
	if (positions.empty()) {
		return;
	}

	glEnable(GL_DEPTH_TEST);

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();
	const auto& eyePos = camera.getPos().toArray();

	assert(GL_NO_ERROR == glGetError());

	glUseProgram(shader.getId());

	const std::vector< float > lightPos = { -10.0f, 10.0f, 10.0f };

	const GLint lightLoc = glGetUniformLocation(shader.getId(), "lightPosition");
	glUniform3fv(lightLoc, 1, &(lightPos.front()));


	glBindFragDataLocation(shader.getId(), 0, "fragColor");
	assert(GL_NO_ERROR == glGetError());

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());
	glUniform3fv(shader.getUniformLocation("eyePosition"), 1, eyePos.data());
	assert(GL_NO_ERROR == glGetError());


	glVertexAttribPointer(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("normal"), 3, GL_FLOAT, GL_FALSE, 0, normals.data());
	//glVertexAttribPointer(location.)
	assert(GL_NO_ERROR == glGetError());


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	assert(GL_NO_ERROR == glGetError());


	glDrawArrays(GL_TRIANGLES, 0, positions.size() / 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	glUseProgram(0);

	const GLenum error = glGetError();
	assert(GL_NO_ERROR == error);

	glDisable(GL_DEPTH_TEST);
}
