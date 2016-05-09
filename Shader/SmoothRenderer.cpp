#include "SmoothRenderer.h"
#include "../Graphics/Material.h"
#include "../Graphics/VisualPolygon.h"
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
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec3 normal;" << std::endl
		<< "out vec3 vColor;" << std::endl
		<< "out vec3 vNormal;" << std::endl
		<< "uniform mat4 projectionMatrix;"
		<< "uniform mat4 modelviewMatrix;"
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	vColor = vec3(0.0, 0.0, 0.0);" << std::endl
		<< "	vNormal = normalize(normal);" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string SmoothRenderer::getBuildinFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 vColor;" << std::endl
		<< "in vec3 vNormal;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "uniform vec3 lightPosition;" << std::endl
		<< "uniform vec3 eyePosition;" << std::endl
		<< "uniform vec3 ambientColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	vec3 s = normalize(lightPosition - eyePosition);" << std::endl
		<< "	vec3 v = normalize(-eyePosition.xyz);" << std::endl
		<< "	vec3 n = vNormal;" << std::endl
		<< "	vec3 r = reflect(-s,n);" << std::endl
		<< "	vec3 color = vColor;" << std::endl
		<< "	vec3 diffuseColor = max(dot(s, n), 0.0) * vec3(0.0, 0.0, 1.0);" << std::endl
		<< "	float sDotN = max( dot(s, n), 0.0);" << std::endl
		<< "	vec3 specularColor = vec3(0.0, 0.0, 0.0);" << std::endl
		<< "	if( sDotN > 0.0) {" << std::endl
		<< "		specularColor = vec3(1.0, 0.0, 0.0) * pow(max(dot(r,v), 0.0), 1.0);" << std::endl
		<< "	}" << std::endl
		<< "	fragColor = vec4(color + diffuseColor + specularColor + ambientColor, 1.0);" << std::endl
		<< "}" << std::endl;
	return stream.str();
}


void SmoothRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");
	shader.findUniformLocation("eyePosition");
	shader.findUniformLocation("ambientColor");
	shader.findUniformLocation("lightPosition");


	shader.findAttribLocation("position");
	shader.findAttribLocation("normal");
}


void SmoothRenderer::render(const ICamera<float>& camera, const TriangleBuffer& buffer, const PointLight<float>& light, const Material& material)
{
	const auto& indices = buffer.getIndices();
	const auto& positions = buffer.getPositions().get();// buffers[0].get();
	const auto& normals = buffer.getNormals().get();//buffers[1].get();
	if (positions.empty()) {
		return;
	}

	glEnable(GL_DEPTH_TEST);

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();
	const auto& eyePos = camera.getPosition().toArray();
	const auto& ambient = material.getAmbient().toArray3();

	assert(GL_NO_ERROR == glGetError());

	glUseProgram(shader.getId());

	const auto& lightPos = light.getPos().toArray();//{ -10.0f, 10.0f, 10.0f };

	const auto lightLoc = glGetUniformLocation(shader.getId(), "lightPosition");
	glUniform3fv(lightLoc, 1, lightPos.data());

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());
	glUniform3fv(shader.getUniformLocation("eyePosition"), 1, eyePos.data());
	glUniform3fv(shader.getUniformLocation("ambientColor"), 1, ambient.data());

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

void SmoothRenderer::render(const ICamera<float>& camera, const TriangleBuffer& buffer, const PointLight<float>& light, const std::vector<MaterialMap>& materials)
{
	const auto& positions = buffer.getPositions().get();// buffers[0].get();
	const auto& normals = buffer.getNormals().get();//buffers[1].get();
	if (positions.empty()) {
		return;
	}

	glEnable(GL_DEPTH_TEST);

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();
	const auto& eyePos = camera.getPosition().toArray();

	assert(GL_NO_ERROR == glGetError());

	glUseProgram(shader.getId());

	const auto& lightPos = light.getPos().toArray();//{ -10.0f, 10.0f, 10.0f };

	const auto lightLoc = glGetUniformLocation(shader.getId(), "lightPosition");
	glUniform3fv(lightLoc, 1, lightPos.data());

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

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

	for (auto& m : materials) {
		const auto indices = buffer.getIndices(m.getStartFaceIndex(), m.getEndFaceIndex());
		const auto& ambient = m.getMaterial().getAmbient().toArray3();

		glUniform3fv(shader.getUniformLocation("ambientColor"), 1, ambient.data());


		//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size() / 3));
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	glUseProgram(0);

	const GLenum error = glGetError();
	assert(GL_NO_ERROR == error);

	glDisable(GL_DEPTH_TEST);
}
