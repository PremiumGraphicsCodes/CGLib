#include "ParticleDepthRenderer.h"

#include <sstream>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool ParticleDepthRenderer::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string ParticleDepthRenderer::getBuildinVertexShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in float pointSize;" << std::endl
		<< "out float vSize;" << std::endl
		<< "out vec4 vPosition;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform mat4 modelviewMatrix;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	gl_PointSize = pointSize / gl_Position.w;" << std::endl
		<< "	vSize = gl_PointSize;" << std::endl
		<< "	vPosition = modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "}" << std::endl;
	bool b = vertexShader.compile(stream.str(), ShaderUnit::Stage::VERTEX);
	return stream.str();
}

std::string ParticleDepthRenderer::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "in float vSize;" << std::endl
		<< "in vec4 vPosition;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	vec3 coord;" << std::endl
		<< "	coord.xy = gl_PointCoord * 2.0 - 1.0;" << std::endl
		<< "	float distSquared = dot(coord.xy, coord.xy);" << std::endl
		<< "	if (distSquared > 1.0) {"
		<< "		discard;"
		<< "	}" << std::endl
		<< "	coord.z = -sqrt(1.0 - distSquared);" << std::endl
		<< "	vec4 pixelPos = vPosition + vSize * vec4(coord.xyz, 1.0);" << std::endl
		<< "	vec4 clipSpacePos = projectionMatrix * pixelPos;" << std::endl
		<< "	float depth = clipSpacePos.z / clipSpacePos.w;" << std::endl
		<< "	gl_FragDepth = depth;" << std::endl
		<< "	fragColor.rgb = vec3(depth);" << std::endl
		<< "	fragColor.a = 1.0;" << std::endl
		<< "}" << std::endl;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void ParticleDepthRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");
	shader.findUniformLocation("modelviewMatrix");

	shader.findAttribLocation("position");
	shader.findAttribLocation("pointSize");
}


void ParticleDepthRenderer::render(const ICamera<float>& camera, const PointBuffer& buffer)
{
	const auto positions = buffer.getPosition().get();
	const auto colors = buffer.getColor().get();
	const auto sizes = buffer.getSize().get();

	if (positions.empty()) {
		return;
	}

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();

	glEnable(GL_DEPTH_TEST);


	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);


	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glDepthMask(GL_FALSE);
	//glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());

	glVertexAttribPointer(shader.getAttribLocation("positions"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
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

	//glDisable(GL_BLEND);
	//glDepthMask(GL_TRUE);


	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);

	glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}
