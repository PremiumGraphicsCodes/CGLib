#include "NormalRenderer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint scale;
		GLuint position;
		GLuint vector;
		
		Location(const GLuint id) {
			projectionMatrix = glGetUniformLocation(id, "projectionMatrix");
			modelviewMatrix = glGetUniformLocation(id, "modelviewMatrix");
			assert(projectionMatrix != -1);
			assert(modelviewMatrix != -1);
			scale = glGetUniformLocation(id, "scale");
			assert(scale != -1);
			position = glGetAttribLocation(id, "position");
			vector = glGetAttribLocation(id, "vector");
			assert(position != -1);
			assert(vector != -1);
		}
	};
}

template<typename GeomType>
void NormalRenderer<GeomType>::render(const ICamera<GeomType>& camera)
{
	if (buffers.size() < 2) {
		return;
	}
	const auto& positions = buffers[0].get();
	const auto& normals = buffers[1].get();
	if (positions.empty() || normals.empty()) {
		return;
	}

	const auto& location = Location(shader.getId());

	const auto& perspectiveMatrix = camera.getProjectionMatrix();
	const auto& modelviewMatrix = camera.getModelviewMatrix();

	assert(GL_NO_ERROR == glGetError());

	glLineWidth(1.0f);

	glUseProgram(shader.getId());

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, &(perspectiveMatrix.toArray().front()));
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, &(modelviewMatrix.toArray().front()));
	glUniform1f(location.scale, scale);

	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, &(positions.front()));
	glVertexAttribPointer(location.vector, 3, GL_FLOAT, GL_FALSE, 0, &(normals.front()));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_POINTS, 0, positions.size() / 3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);


	assert(GL_NO_ERROR == glGetError());
}

template class NormalRenderer<float>;