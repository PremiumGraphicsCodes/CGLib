#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"
#include "CubeMapSample.h"

#include <iostream>

#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;


CubeMapSample::CubeMapSample()
{
}


std::string CubeMapSample::getVertexShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec3 normal;" << std::endl
		<< "out vec3 reflectDir;" << std::endl
		<< "uniform vec3 eyePosition;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	vec3 worldView = normalize( eyePosition - position );" << std::endl
		<< "	reflectDir = reflect(-position, normal);" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "}" << std::endl;
	vertexShader.compile(stream.str(), Crystal::Shader::ShaderUnit::Stage::VERTEX);
	return stream.str();
}

std::string CubeMapSample::getFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 reflectDir;" << std::endl
		<< "uniform samplerCube cubeMapTex;" << std::endl
		<< "uniform float reflectFactor;" << std::endl
		<< "uniform vec4 materialColor;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main() {" << std::endl
		<< "	vec4 cubeMapColor = texture(cubeMapTex, reflectDir);" << std::endl
		<< "	fragColor = mix(materialColor, cubeMapColor, reflectFactor);" << std::endl
//		<< "	fragColor.rgb = vec3(1.0);" << std::endl
		<< "}" << std::endl;
	fragmentShader.compile(stream.str(), Crystal::Shader::ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void CubeMapSample::setup()
{
	const auto& vsSource = getVertexShaderSource();
	const auto& fsSource = getFragmentShaderSource();
	shader.build(vsSource, fsSource);


	Crystal::Graphics::Image<float> image(2, 2);
	image.setColor(0, 0, ColorRGBA<float>(0.0, 0.0, 1.0, 1.0));
	image.setColor(1, 1, ColorRGBA<float>(0.0, 0.0, 1.0, 1.0));
	cubeMapTexture.create(image, 10);

	shader.findAttribLocation("position");
	shader.findAttribLocation("normal");
	shader.findUniformLocation("eyePosition");
	shader.findUniformLocation("modelviewMatrix");
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("materialColor");
	shader.findUniformLocation("cubeMapTex");
	shader.findUniformLocation("reflectFactor");

	//renderer.build(512, 512);

	Crystal::Polygon::PolygonObject polygon;
	polygon.add(Crystal::Math::Box3d<float>(Crystal::Math::Vector3d<float>(0.0, 0.0, 0.0), Crystal::Math::Vector3d<float>(1.0, 1.0, 1.0)));
	buffer.clear();
	buffer.add(polygon);
	//buffer.add(Triangle<float>(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(1.0f, 0.0, 0.0), Vector3d<float>(1.0f, 1.0f, 0.0)));
}

void CubeMapSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	const auto& indices = buffer.getIndices();
	const auto& positions = buffer.getPositions().get();// buffers[0].get();
	const auto& normals = buffer.getNormals().get();//buffers[1].get();
	if (positions.empty()) {
		return;
	}

	cubeMapTexture.bind();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	//cubeMapTexture.bind();

	glUniform1f(shader.getUniformLocation("reflectFactor"), 0.8f);
	assert(GL_NO_ERROR == glGetError());

	glUniform1i(shader.getUniformLocation("cubeMapTex"), 10);// volumeTexture.getId());
	glUniform3fv(shader.getUniformLocation("eyePosition"), 1, camera.getPosition().toArray().data());
	assert(GL_NO_ERROR == glGetError());


	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"),1, false, camera.getModelviewMatrix().toArray().data());
	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, false, camera.getProjectionMatrix().toArray().data());


	assert(GL_NO_ERROR == glGetError());

	glVertexAttribPointer(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("normal"), 3, GL_FLOAT, GL_FALSE, 0, normals.data());

	assert(GL_NO_ERROR == glGetError());

	ColorRGBA<float> color(1.0, 0.0, 1.0, 1.0);
	glUniform4fv(shader.getUniformLocation("materialColor"), 1, color.toArray4().data());

	assert(GL_NO_ERROR == glGetError());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	cubeMapTexture.unbind();
	glDisable(GL_DEPTH_TEST);


	glUseProgram(0);
}
