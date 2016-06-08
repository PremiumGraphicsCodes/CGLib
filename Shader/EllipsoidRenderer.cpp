#include "EllipsoidRenderer.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool EllipsoidRenderer::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

/*
const auto x00 = (1.0f - 2.0f * y * y - 2.0f * z * z);
const auto x01 = (2.0f * x * y - 2.0f * z * w);
const auto x02 = (2.0f * x * z + 2.0f * y * w);

const auto x10 = (2.0f * x * y + 2.0f * z * w);
const auto x11 = (1.0f - 2.0f * x * x - 2.0f * z * z);
const auto x12 = (2.0f * y * z - 2.0f * x * w);

const auto x20 = (2.0f * x * z - 2.0f * y * w);
const auto x21 = (2.0f * y * z + 2.0f * x * w);
const auto x22 = (1.0f - 2.0f * x * x - 2.0f * y * y);
*/
namespace {
	std::string matrixToQuaternion() {
		std::ostringstream stream;
		stream
			<< "mat3 toMatrix(vec4 q) {" << std::endl
			<< "	float x = q[0]; " << std::endl
			<< "	float y = q[1]; " << std::endl
			<< "	float z = q[2]; " << std::endl
			<< "	float w = q[3]; " << std::endl
			<< "	float x00 = 1 - 2*y*y - 2.0*z*z;" << std::endl
			<< "	float x01 = 2 * x*y - 2.0*z*w;" << std::endl
			<< "	float x02 = 2 * x*z + 2.0*y*w;" << std::endl
			<< "	float x10 = 2 * x*y + 2*z*w;" << std::endl
			<< "	float x11 = 1 - 2*x*x - 2 *z*z;" << std::endl
			<< "	float x12 = 2*y*z - 2*x*w;" << std::endl
			<< "	float x20 = 2*x*z - 2*y*w;" << std::endl
			<< "	float x21 = 2*y*z + 2*x*w;" << std::endl
			<< "	float x22 = 1 - 2*x*x - 2*y*y;" << std::endl
			<< "	return mat3(x00, x01, x02, x10, x11, x12, x20, x21, x22); " << std::endl
			//<< "	return mat3(1,0,0, 0,1,0, 0,0, 1); " << std::endl

			<< "}" << std::endl;
		return stream.str();
	}
}

std::string EllipsoidRenderer::getBuildinVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in int id;" << std::endl
		<< "in float pointSize;" << std::endl
		<< "in vec4 color;" << std::endl
		<< "in vec3 radii;" << std::endl
		<< "in vec4 orientation;" << std::endl
		<< "out vec4 vColor;" << std::endl
		<< "out vec3 vRadii;" << std::endl
		<< "out vec4 vOrientation;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	gl_PointSize = 100 / gl_Position.w;" << std::endl
		<< "	vColor = color;" << std::endl
		<< "	vRadii = radii;" << std::endl
		<< "	vOrientation = orientation;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string EllipsoidRenderer::getBuildinFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec4 vColor;" << std::endl
		<< "in vec3 vRadii;" << std::endl
		<< "in vec4 vOrientation;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< matrixToQuaternion() << std::endl
		<< "void main(void) {" << std::endl
		<< "	vec3 coord;" << std::endl
		<< "	coord.xy = gl_PointCoord * 2.0 - 1.0;" << std::endl
		<< "	float distSquared = sqrt(dot(coord.xy, coord.xy));" << std::endl
		<< "	coord.z = 1.0 - distSquared;" << std::endl
		<< "	mat3 rotationMatrix = toMatrix(vOrientation);" << std::endl
		<< "	mat3 matrix = rotationMatrix * mat3(vRadii.x, 0, 0, 0, vRadii.y, 0, 0, 0, vRadii.z) * inverse(rotationMatrix);" << std::endl
		<< "	coord = matrix * coord;" << std::endl
		<< "	distSquared = (coord.x * coord.x) / (vRadii.x * vRadii.x) + (coord.y * coord.y) / (vRadii.y * vRadii.y) + (coord.z * coord.z) / (vRadii.z * vRadii.z);" << std::endl
		<< "	if (distSquared > 1.0 ) {"
		<< "		discard;"
		<< "	}" << std::endl
	//	<< "	fragColor.rgb = vRadii;" << std::endl
		<< "	fragColor.rgba = vColor;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

void EllipsoidRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");

	shader.findAttribLocation("position");
	shader.findAttribLocation("color");
	shader.findAttribLocation("radii");
	shader.findAttribLocation("orientation");
}


void EllipsoidRenderer::render(const ICamera<float>& camera, const OrientedParticleBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();
	const auto& colors = buffer.getColor().get();
	const auto& radii = buffer.getRadii().get();
	const auto& orientation = buffer.getOrientation().get();


	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);

	//glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(shader.getAttribLocation("positions"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("color"), 4, GL_FLOAT, GL_FALSE, 0, colors.data());
	glVertexAttribPointer(shader.getAttribLocation("radii"), 3, GL_FLOAT, GL_FALSE, 0, radii.data());
	glVertexAttribPointer(shader.getAttribLocation("orientation"), 4, GL_FLOAT, GL_FALSE, 0, orientation.data());


	//const auto positions = buffer.getPositions();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(positions.size() / 3));

	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glDisable(GL_DEPTH_TEST);


	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);


	glUseProgram(0);
}
