#include "SmoothRenderer.h"
#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool SmoothRenderer::build()
{
	const auto& vShader = getBuildinVertexShaderSource();
	const auto& fShader = getBuildinFragmentShaderSource();
	bool b = shader.build(vShader, fShader);
	findLocation();
	return b;
}

std::string SmoothRenderer::getBuildinVertexShaderSource() const
{
	std::ostringstream stream;
	stream << "#version 150" << std::endl;
	stream << "in vec3 position;" << std::endl;
	stream << "in vec3 normal;" << std::endl;
	stream << "out vec3 vColor;" << std::endl;
	stream << "out vec3 vNormal;" << std::endl;
	stream << "uniform mat4 projectionMatrix;" << std::endl;
	stream << "uniform mat4 modelviewMatrix;" << std::endl;
	stream << "void main(void) {" << std::endl;
	stream << "gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl;
	stream << "vColor = vec3(0.0, 0.0, 0.0);" << std::endl;
	stream << "vNormal = normalize(normal);" << std::endl;
	stream << "}" << std::endl;
	return stream.str();
}

std::string SmoothRenderer::getBuildinFragmentShaderSource() const
{
	std::ostringstream stream;
	stream << "#version 150" << std::endl;
	stream << "in vec3 vColor;" << std::endl;
	stream << "in vec3 vNormal;" << std::endl;
	stream << "out vec4 fragColor;" << std::endl;
	stream << "uniform vec3 lightPosition;" << std::endl;
	stream << "uniform vec3 eyePosition;" << std::endl;
	stream << "void main(void) {" << std::endl;
	stream << "vec3 s = normalize(lightPosition - eyePosition);" << std::endl;
	stream << "vec3 n = vNormal;" << std::endl;
	stream << "vec3 color = vColor;" << std::endl;
	stream << "vec3 diffuseColor = max(dot(s, n), 0.0) * vec3(0.0, 0.0, 1.0);" << std::endl;
	stream << "vec3 ambientColor = vec3(0.2, 0.2, 0.2);" << std::endl;
	stream << "fragColor = vec4(color + diffuseColor + ambientColor, 1.0);" << std::endl;
	stream << "}" << std::endl;
	return stream.str();
}


void SmoothRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");
	shader.findUniformLocation("eyePosition");

	shader.findAttribLocation("position");
	shader.findAttribLocation("normal");
}


void SmoothRenderer::render(const ICamera<float>& camera, const TriangleBuffer& buffer)
{
	const auto& indices = buffer.indices;
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


	//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size() / 3));
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	glUseProgram(0);

	const GLenum error = glGetError();
	assert(GL_NO_ERROR == error);

	glDisable(GL_DEPTH_TEST);
}
