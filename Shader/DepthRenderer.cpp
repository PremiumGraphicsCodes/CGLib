#include "DepthRenderer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		Location(GLuint id) {
			projectionMatrix = glGetUniformLocation(id, "projectionMatrix");
			modelviewMatrix = glGetUniformLocation(id, "modelviewMatrix");
			assert(projectionMatrix != -1);
			assert(modelviewMatrix != -1);
			position = glGetAttribLocation(id, "position");
			assert(position != -1);
		}
	};
}


void DepthRenderer::render(const ICamera<float>& camera)
{
	const auto positions = buffers[0].get();
	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	glUseProgram(shader.getId());

	Location location(shader.getId());

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, &(projectionMatrix.toArray().front()));
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, &(modelviewMatrix.front()));

	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	//glVertexAttribIPointer(location.id, 1, GL_INT, 0, &(ids.front()));


	//const auto positions = buffer.getPositions();
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(positions.size()) / 3);

	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");


	glUseProgram(0);

}