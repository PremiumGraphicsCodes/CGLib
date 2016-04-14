#include "PointRenderer.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool PointRenderer::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string PointRenderer::getBuildinVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in int id;" << std::endl
		<< "in float pointSize;" << std::endl
		<< "in vec4 color;" << std::endl
		<< "out vec4 vColor;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	gl_PointSize = pointSize / gl_Position.w;" << std::endl
		<< "	vColor = color;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string PointRenderer::getBuildinFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec4 vColor;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	vec2 coord = gl_PointCoord * 2.0 - 1.0;" << std::endl
		<< "	float distSquared = 1.0 - dot(coord, coord);" << std::endl
		<< "	if (distSquared < 0.0) {" << std::endl
		<< "		discard;" << std::endl
		<< "	}" << std::endl
		<< "	fragColor.rgba = vColor;" << std::endl
		<< "	fragColor.a = sqrt(distSquared) * vColor.a;" << std::endl
		<< "	fragColor.a = 0.1;//sqrt(distSquared);" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

void PointRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");

	shader.findAttribLocation("position");
	shader.findAttribLocation("color");
	shader.findAttribLocation("pointSize");
}


void PointRenderer::render(const ICamera<float>& camera, const PointBuffer& buffer, bool doBlend)
{
	const auto positions = buffer.getPosition().get();
	const auto colors = buffer.getColor().get();
	const auto sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	if (doBlend) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glDepthMask(GL_FALSE);
		glDisable(GL_DEPTH_TEST);
	}
	else {
		glEnable(GL_DEPTH_TEST);
	}

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);

	//glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(shader.getAttribLocation("positions"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("color"), 4, GL_FLOAT, GL_FALSE, 0, colors.data());
	glVertexAttribPointer(shader.getAttribLocation("pointSize"), 1, GL_FLOAT, GL_FALSE, 0, sizes.data());


	//const auto positions = buffer.getPositions();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawArrays(GL_POINTS, 0, positions.size() / 3);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	if (doBlend) {
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}
	else {
		glDisable(GL_DEPTH_TEST);
	}


	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);


	glUseProgram(0);
}
