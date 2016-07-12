#include "stdafx.h"
#include "SkyBoxRenderer.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool SkyBoxRenderer::build()
{
	const auto& vsSource = getBuiltinVertexShaderSource();
	const auto& fsSource = getBuiltinFragmentShaderSource();
	const bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string SkyBoxRenderer::getBuiltinVertexShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "out vec3 reflectDir;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	reflectDir = position;" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "}" << std::endl;
	ShaderUnit vertexShader;
	vertexShader.compile(stream.str(), Crystal::Shader::ShaderUnit::Stage::VERTEX);
	return stream.str();
}

std::string SkyBoxRenderer::getBuiltinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 reflectDir;" << std::endl
		<< "uniform samplerCube cubeMapTex;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main() {" << std::endl
		<< "	vec4 reflectColor = texture(cubeMapTex, reflectDir);" << std::endl
		<< "	fragColor = reflectColor;" << std::endl
		<< "}" << std::endl;
	ShaderUnit fragmentShader;
	fragmentShader.compile(stream.str(), Crystal::Shader::ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void SkyBoxRenderer::findLocation()
{
	shader.findAttribLocation("position");
	shader.findUniformLocation("modelviewMatrix");
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("cubeMapTex");
}

void SkyBoxRenderer::render(const CubeMapTextureObject& cubeMapTexture, const ICamera<float>& camera)
{
	TriangleBuffer buffer;
	Crystal::Core::PolygonMesh polygon;
	//const Box3d<float> box(Vector3d<float>(-100.0, 0.0, -20.0), Vector3d<float>(100.0, 20.0, 20.0));
	//polygon.add(box);
	Crystal::Math::Box3d<float> box(Crystal::Math::Vector3d<float>(-100.0, -100.0, -100.0), Crystal::Math::Vector3d<float>(100.0, 100.0, 100.0));
	//polygon.add(box);
	buffer.add(polygon);

	const auto& indices = buffer.getIndices();
	const auto& positions = buffer.getPositions().get();// buffers[0].get();
	const auto& normals = buffer.getNormals().get();//buffers[1].get();
	if (positions.empty()) {
		return;
	}

	cubeMapTexture.bind();


	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	assert(GL_NO_ERROR == glGetError());

	glUniform1i(shader.getUniformLocation("cubeMapTex"), cubeMapTexture.getId());// volumeTexture.getId());
	assert(GL_NO_ERROR == glGetError());


	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, false, camera.getModelviewMatrix().toArray().data());
	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, false, camera.getProjectionMatrix().toArray().data());


	glVertexAttribPointer(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	cubeMapTexture.unbind();
	glDisable(GL_DEPTH_TEST);


	glUseProgram(0);

}
