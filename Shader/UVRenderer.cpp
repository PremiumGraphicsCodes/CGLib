#include "stdafx.h"
#include "UVRenderer.h"
#include <sstream>

#include "ShaderHandler.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	std::string shaderName = "uv";
}

bool UVRenderer::build()
{
	const auto& vShader = getBuildinVertexShaderSource();
	const auto& fShader = getBuildinFragmentShaderSource();

	bool result = ShaderHandler::getInstance()->build(shaderName, vShader, fShader);
	if (result) {
		set(ShaderHandler::getInstance()->get(shaderName));
	}
	this->shader = ShaderHandler::getInstance()->get(shaderName);

	return result;
}

std::string UVRenderer::getBuildinVertexShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec3 texCoord;" << std::endl
		<< "out vec3 vTexCoord;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	vTexCoord = texCoord;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string UVRenderer::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 vTexCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	fragColor = vec4(vTexCoord,1.0);" << std::endl
		<< "}" << std::endl;
	return stream.str();
}


void UVRenderer::set(ShaderObject* shader)
{
	this->shader = shader;
	shader->findUniformLocation("projectionMatrix");
	shader->findUniformLocation("modelviewMatrix");

	shader->findAttribLocation("position");
	shader->findAttribLocation("texCoord");
}


void UVRenderer::render(const ICamera<float>& camera, const TriangleBuffer& buffer)
{
	const auto& indices = buffer.getIndices();
	const auto& positions = buffer.getPositions().get();// buffers[0].get();
	const auto& texCoords = buffer.getTexCoords().get();//buffers[1].get();
	if (positions.empty()) {
		return;
	}

	glEnable(GL_DEPTH_TEST);

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	assert(GL_NO_ERROR == glGetError());

	glUseProgram(shader->getId());


	glBindFragDataLocation(shader->getId(), 0, "fragColor");

	glUniformMatrix4fv(shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader->getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	assert(GL_NO_ERROR == glGetError());

	glVertexAttribPointer(shader->getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader->getAttribLocation("texCoord"), 3, GL_FLOAT, GL_FALSE, 0, texCoords.data());
	//glVertexAttribPointer(location.)
	assert(GL_NO_ERROR == glGetError());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	assert(GL_NO_ERROR == glGetError());

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glUseProgram(0);

	glDisable(GL_DEPTH_TEST);
}
