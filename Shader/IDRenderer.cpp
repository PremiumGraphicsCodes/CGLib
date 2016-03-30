#include "IDRenderer.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool IDRenderer::buildBuildInShader()
{
	const auto& vShader = getBuildinVertexShaderSource();
	const auto& fShader = getBuildinFragmentShaderSource();
	return shader.build(vShader, fShader);
}

std::string IDRenderer::getBuildinVertexShaderSource() const
{
	std::ostringstream stream;
	stream << "#version 150" << std::endl;
	stream << "in vec3 position;" << std::endl;
	stream << "in vec4 id;" << std::endl;
	stream << "out vec4 vId;" << std::endl;
	stream << "uniform mat4 projectionMatrix;" << std::endl;
	stream << "uniform mat4 modelviewMatrix;" << std::endl;
	stream << "void main(void)" << std::endl;
	stream << "{" << std::endl;
	stream << "gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl;
	stream << "vId = id;" << std::endl;
	stream << "}";
	return stream.str();
}

std::string IDRenderer::getBuildinFragmentShaderSource() const
{
	std::ostringstream stream;
	stream << "#version 150" << std::endl;
	stream << "in vec4 vId;" << std::endl;
	stream << "out vec4 fragColor;" << std::endl;
	stream << "void main(void) {" << std::endl;
	stream << "fragColor = vId;" << std::endl;
	stream << "}" << std::endl;
	return stream.str();
}


void IDRenderer::findLocation()
{
	location.projectionMatrix = glGetUniformLocation(shader.getId(), "projectionMatrix");
	location.modelviewMatrix = glGetUniformLocation(shader.getId(), "modelviewMatrix");

	location.position = glGetAttribLocation(shader.getId(), "position");
	location.id = glGetAttribLocation(shader.getId(), "id");
}

void IDRenderer::render(const ICamera<float>& camera)
{
	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	assert(GL_NO_ERROR == glGetError());

	glUseProgram(shader.getId());

	glUniformMatrix4fv(location.projectionMatrix, 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(location.modelviewMatrix, 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(location.position, 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribIPointer(location.id, 1, GL_INT, 0, ids.data());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//const auto positions = buffer.getPositions();

	glDrawArrays(GL_LINES, 0, positions.size() / 3);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glUseProgram(0);

}