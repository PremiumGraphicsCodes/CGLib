#include "stdafx.h"
#include "CubeMapRenderer.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool CubeMapRenderer::build()
{
	const auto& vsSource = getBuiltinVertexShaderSource();
	const auto& fsSource = getBuiltinFragmentShaderSource();
	const bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string CubeMapRenderer::getBuiltinVertexShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec3 normal;" << std::endl
		<< "out vec3 reflectDir;" << std::endl
		<< "out vec3 refractDir;" << std::endl
		<< "uniform vec3 eyePosition;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		//<< "uniform float refractFactor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	vec3 worldPosition = vec3(modelviewMatrix * vec4(position,1.0));" << std::endl
		<< "	vec3 worldNormal = vec3(modelviewMatrix * vec4(normal,0.0));" << std::endl
		<< "	vec3 worldView = normalize( eyePosition - worldPosition );" << std::endl
		<< "	reflectDir = reflect(-worldView, worldNormal);" << std::endl
		<< "	refractDir = refract(-worldView, worldNormal, 1.33);" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "}" << std::endl;
	ShaderUnit vertexShader;
	vertexShader.compile(stream.str(), Crystal::Shader::ShaderUnit::Stage::VERTEX);
	return stream.str();
}

std::string CubeMapRenderer::getBuiltinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 reflectDir;" << std::endl
		<< "in vec3 refractDir;" << std::endl
		<< "uniform samplerCube cubeMapTex;" << std::endl
		//<< "uniform float reflectFactor;" << std::endl
		//<< "uniform float refractFactor;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main() {" << std::endl
		<< "	vec4 reflectColor = texture(cubeMapTex, reflectDir);" << std::endl
		<< "	vec4 refractColor = texture(cubeMapTex, refractDir);" << std::endl
		<< "	fragColor = mix(refractColor, reflectColor, 1.0);" << std::endl
		//<< "	fragColor.rgb = refractDir;" << std::endl
		<< "}" << std::endl;
	ShaderUnit fragmentShader;
	fragmentShader.compile(stream.str(), Crystal::Shader::ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void CubeMapRenderer::findLocation()
{
	shader.findAttribLocation("position");
	shader.findAttribLocation("normal");
	shader.findUniformLocation("eyePosition");
	shader.findUniformLocation("modelviewMatrix");
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("cubeMapTex");
//	shader.findUniformLocation("reflectFactor");
//	shader.findUniformLocation("refractFactor");
}

void CubeMapRenderer::render(const CubeMapTextureObject& cubeMapTexture, const ICamera<float>& camera, const TriangleBuffer& buffer)
{
	const auto& positions = buffer.getPositions().get();// buffers[0].get();
	const auto& normals = buffer.getNormals().get();//buffers[1].get();
	if (positions.empty()) {
		return;
	}

	cubeMapTexture.bind();


	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	//cubeMapTexture.bind();

//	glUniform1f(shader.getUniformLocation("reflectFactor"), 0.8f);
//	glUniform1f(shader.getUniformLocation("refractFactor"), 1.2f);

	assert(GL_NO_ERROR == glGetError());

	glUniform1i(shader.getUniformLocation("cubeMapTex"), cubeMapTexture.getId());// volumeTexture.getId());
	glUniform3fv(shader.getUniformLocation("eyePosition"), 1, camera.getPosition().toArray().data());
	assert(GL_NO_ERROR == glGetError());


	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, false, camera.getModelviewMatrix().toArray().data());
	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, false, camera.getProjectionMatrix().toArray().data());


	assert(GL_NO_ERROR == glGetError());

	glVertexAttribPointer(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("normal"), 3, GL_FLOAT, GL_FALSE, 0, normals.data());

	assert(GL_NO_ERROR == glGetError());

	assert(GL_NO_ERROR == glGetError());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	for (const auto& b : buffer.getBlocks()) {
		const auto& indices = b.getIndices();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	cubeMapTexture.unbind();
	glDisable(GL_DEPTH_TEST);


	glUseProgram(0);

}
