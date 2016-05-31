#include "SSThicknessRenderer.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool SSThicknessRenderer::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string SSThicknessRenderer::getBuildinVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in int id;" << std::endl
		<< "in float pointSize;" << std::endl
//		<< "in vec4 color;" << std::endl
//		<< "out vec4 vColor;" << std::endl
		<< "in vec3 matrixRow1;" << std::endl
		<< "in vec3 matrixRow2;" << std::endl
		<< "in vec3 matrixRow3;" << std::endl
		<< "out mat3 vMatrix;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	gl_PointSize = pointSize / gl_Position.w;" << std::endl
		<< "	vMatrix = mat3(matrixRow1, matrixRow2, matrixRow3);" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string SSThicknessRenderer::getBuildinFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in mat3 vMatrix;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	vec3 coord;" << std::endl
		<< "	coord.xy = gl_PointCoord * 2.0 - 1.0;" << std::endl
		<< "	float distSquared = sqrt(dot(coord.xy, coord.xy));" << std::endl
		<< "	coord.z = 1.0 - distSquared;" << std::endl
		<< "	coord = vMatrix * coord;" << std::endl
		<< "	distSquared = dot(coord.xyz, coord.xyz);" << std::endl
		<< "	if (distSquared > 1.0) {"
		<< "		discard;"
		<< "	}" << std::endl
//		<< "	fragColor.rgba = vec4(sqrt(distSquared) * 0.1);" << std::endl
	//	<< "	fragColor.a = sqrt(distSquared) * vColor.a;" << std::endl
		<< "	fragColor = vec4(0.05 * coord.z);" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

void SSThicknessRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");

	shader.findAttribLocation("position");
	//shader.findAttribLocation("color");
	shader.findAttribLocation("pointSize");
	shader.findAttribLocation("matrixRow1");
	shader.findAttribLocation("matrixRow2");
	shader.findAttribLocation("matrixRow3");
}


void SSThicknessRenderer::render(const ICamera<float>& camera, const EllipsoidBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();
	const auto& sizes = buffer.getSize().get();
	const auto& matrixRow1 = buffer.getMatrixRow1().get();
	const auto& matrixRow2 = buffer.getMatrixRow2().get();
	const auto& matrixRow3 = buffer.getMatrixRow3().get();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
	glBlendFunc(GL_ONE, GL_ONE);

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glUseProgram(shader.getId());

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(shader.getAttribLocation("positions"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("pointSize"), 1, GL_FLOAT, GL_FALSE, 0, sizes.data());
	glVertexAttribPointer(shader.getAttribLocation("matrixRow1"), 3, GL_FLOAT, GL_FALSE, 0, matrixRow1.data());
	glVertexAttribPointer(shader.getAttribLocation("matrixRow2"), 3, GL_FLOAT, GL_FALSE, 0, matrixRow2.data());
	glVertexAttribPointer(shader.getAttribLocation("matrixRow3"), 3, GL_FLOAT, GL_FALSE, 0, matrixRow3.data());


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);

	glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>( positions.size() / 3 ));

	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);


	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);

	glDepthMask(GL_TRUE);


	glUseProgram(0);
}
