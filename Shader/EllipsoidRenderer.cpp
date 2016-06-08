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
	std::string quaternionToMat3() {
		std::ostringstream stream;
		stream
			<< "mat3 toMat3(vec4 q) {" << std::endl
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

	std::string quaternionToMat4() {
		std::ostringstream stream;
		stream
			<< "mat4 toMat4(vec4 q) {" << std::endl
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
			<< "	return mat4(x00, x01, x02, 0, x10, x11, x12, 0, x20, x21, x22, 0, 0, 0, 0, 1); " << std::endl
			//<< "	return mat3(1,0,0, 0,1,0, 0,0, 1); " << std::endl

			<< "}" << std::endl;
		return stream.str();
	}


	std::string getCubicSpline() {
		std::stringstream stream;
		stream
			<< "float getCubicSpline(const float q) {"
			<< "	float coe = 3.0 / 3.141592;" << std::endl
			<< "	if(q < 1) {" << std::endl
			<< "		return coe * (2.0 / 3.0-q*q + 0.5*q*q*q);" << std::endl
			<< "	}else if( q < 2 ) {" << std::endl
			<< "		return coe * (pow(2-q,3)/6);" << std::endl
			<< "	}" << std::endl
			<< "	return 0.0;" << std::endl
			<< "}" << std::endl;
		return stream.str();
	}

	std::string getCubicSplineByMatrix() {
		std::stringstream stream;
		stream
			<< "float getCubicSpline(vec3 v, mat3 m) {" << std::endl
			<< "	vec3 vv = m * v;" << std::endl
			<< "	float q = length(vv);" << std::endl
			<< "	return determinant(m) * getCubicSpline(q);" << std::endl
			<< "}" << std::endl;
		return stream.str();
	}
}
/*

template<typename T, typename int DIM>
T SPHKernel<T, DIM>::getCubicSpline(const Vector3d<T>& v, const Matrix3d<T>& m)
{
	const auto det = m.getDeterminant();
	const auto vv = v * m;
	const auto q = vv.getLength();
	return det * getCubicSpline(q);
}
*/
std::string EllipsoidRenderer::getBuildinVertexShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec4 color;" << std::endl
		<< "in vec3 radii;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 vColor;" << std::endl
		<< "out vec3 vRadii;" << std::endl
		<< "out vec2 vTexCoord;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< quaternionToMat3() << std::endl
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	vColor = color;" << std::endl
		<< "	vRadii = radii;//(projectionMatrix * vec4(radii,1.0)).xyz;" << std::endl
		<< "	vTexCoord = texCoord;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string EllipsoidRenderer::getBuildinFragmentShaderSource() const
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "in vec4 vColor;" << std::endl
		<< "in vec3 vRadii;" << std::endl
		<< "in vec2 vTexCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< quaternionToMat4() << std::endl
		<< "void main(void) {" << std::endl
		<< "	vec2 coord = vTexCoord;" << std::endl
		//		<< "	mat2 rotationMatrix = mat2(cos(vAngle), -sin(vAngle), sin(vAngle), cos(vAngle));" << std::endl
		<< "	mat2 rotationMatrix = mat2(1,0,0,1);" << std::endl
		<< "	mat2 scalingMatrix = mat2(vRadii.x, 0, 0, vRadii.y);" << std::endl
		<< "	mat2 matrix = rotationMatrix * scalingMatrix * inverse(rotationMatrix);" << std::endl
		<< "	coord = matrix * coord;" << std::endl
		<< "	float distSquared = (coord.x * coord.x) / (vRadii.x * vRadii.x) + (coord.y * coord.y) / (vRadii.y * vRadii.y);" << std::endl
		<< "	if(distSquared > 1.0) {" << std::endl
		<< "		discard;"
		<< "	}" << std::endl
		<< "	fragColor.rgb = vRadii;" << std::endl
		<< "	fragColor.rgba = vColor;" << std::endl
		<< "	fragColor.rgb = vec3(1.0);" << std::endl

		<< "}" << std::endl;
	return stream.str();
}

void EllipsoidRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");

	shader.findAttribLocation("position");
	shader.findAttribLocation("texCoord");
	shader.findAttribLocation("color");
	shader.findAttribLocation("radii");
//	shader.findAttribLocation("orientation");
}


void EllipsoidRenderer::render(const ICamera<float>& camera, const OrientedParticleBuffer& buffer)
{
	const auto& positions = buffer.getPosition().get();
	const auto& colors = buffer.getColor().get();
	const auto& radii = buffer.getRadii().get();
	const auto& orientation = buffer.getOrientation().get();
	const auto& texCoord = buffer.getTexCoord().get();


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

	glVertexAttribPointer(shader.getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader.getAttribLocation("texCoord"), 2, GL_FLOAT, GL_FALSE, 0, texCoord.data());

	glVertexAttribPointer(shader.getAttribLocation("color"), 4, GL_FLOAT, GL_FALSE, 0, colors.data());
	glVertexAttribPointer(shader.getAttribLocation("radii"), 3, GL_FLOAT, GL_FALSE, 0, radii.data());
	//glVertexAttribPointer(shader.getAttribLocation("orientation"), 4, GL_FLOAT, GL_FALSE, 0, orientation.data());


	//const auto positions = buffer.getPositions();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	//glEnableVertexAttribArray(4);

	const auto indices = buffer.getIndices();

	//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size() / 3));


	//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size() / 3));
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());


	//glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	glDisable(GL_DEPTH_TEST);


	//glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	//glDisable(GL_POINT_SPRITE);

	assert(GL_NO_ERROR == glGetError());

	glUseProgram(0);
}
