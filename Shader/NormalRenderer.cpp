#include "stdafx.h"
#include "NormalRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void NormalBuffer::add(const Vector3d<float>& position, const Vector3d<float>& normal, const ColorRGBA<float>& color)
{
	this->position.add(position);
	this->normal.add(normal);
	this->color.add(color);
}

using namespace Crystal::Shader::v330;

bool NormalRenderer::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto gsSource = getBuildinGeometryShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, gsSource, fsSource);
	findLocation();
	return b;
}

std::string NormalRenderer::getBuildinVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 330" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec3 normal;" << std::endl
		<< "in vec4 color;" << std::endl
		<< "out vec4 vNormal;" << std::endl
		<< "out vec4 vColor;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	vColor = color;" << std::endl
		<< "	vNormal = projectionMatrix * modelviewMatrix * vec4(normal,1.0);" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string NormalRenderer::getBuildinGeometryShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 330" << std::endl
		<< "layout(points) in;" << std::endl
		<< "layout(line_strip, max_vertices = 2) out;" << std::endl
		<< "in vec4 vNormal[];" << std::endl
		<< "in vec4 vColor[];" << std::endl
		<< "out vec4 gColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	gl_Position = gl_in[0].gl_Position;" << std::endl
		<< "	gColor = vColor[0];" << std::endl
		<< "	EmitVertex();" << std::endl
		<< "	gl_Position = gl_in[0].gl_Position + vNormal[0];" << std::endl
		<< "	gColor = vColor[0];" << std::endl
		<< "	EmitVertex();" << std::endl
		<< "	EndPrimitive();" << std::endl
		<< "}" << std::endl;
	return stream.str();

}


std::string NormalRenderer::getBuildinFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 330" << std::endl
		<< "in vec4 gColor;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	fragColor.rgba = gColor;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

void NormalRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");

	shader.findAttribLocation("position");
	shader.findAttribLocation("color");
	shader.findAttribLocation("normal");
}


void NormalRenderer::render(const ICamera<float>& camera, const NormalBuffer& buffer)
{
	const auto positions = buffer.getPosition().get();
	const auto colors = buffer.getColor().get();
	const auto normals = buffer.getNormal().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	//glEnable(GL_POINT_SPRITE);

	//glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(shader.getAttribLocation("positions"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("color"), 4, GL_FLOAT, GL_FALSE, 0, colors.data());
	glVertexAttribPointer(shader.getAttribLocation("normal"), 3, GL_FLOAT, GL_FALSE, 0, normals.data());


	//const auto positions = buffer.getPositions();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(positions.size() / 3));

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glDisable(GL_DEPTH_TEST);

	//glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	//glDisable(GL_POINT_SPRITE);

	glUseProgram(0);
}
