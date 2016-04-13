#include "SSCubeMapRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool SSCubeMapRenderer::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string SSCubeMapRenderer::getBuildinVertexShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec2 position;" << std::endl
		<< "out vec2 texCoord;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	texCoord = (position + vec2(1.0,1.0))/2.0;" << std::endl
		<< "	gl_Position = vec4(position, 0.0, 1.0);" << std::endl
		<< "}" << std::endl;
	ShaderUnit vertexShader;
	bool b = vertexShader.compile(stream.str(), ShaderUnit::Stage::VERTEX);
	return stream.str();
}

std::string SSCubeMapRenderer::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform vec3 eyePosition;" << std::endl
		<< "uniform sampler2D depthTex;" << std::endl
		<< "uniform sampler2D normalTex;" << std::endl
		<< "uniform samplerCube cubeMapTex;" << std::endl
		<< "float getDepth(vec2 tCoord){" << std::endl
		<< "	return texture2D(depthTex, tCoord).r;" << std::endl
		<< "}" << std::endl
		<< "vec3 uvToEye(vec2 tCoord, float depth) {" << std::endl
		<< "	vec4 clippingPosition = vec4(tCoord, depth, 1.0);" << std::endl
		<< "	vec4 viewPosition = inverse(projectionMatrix) * clippingPosition;" << std::endl
		<< "    return viewPosition.xyz / viewPosition.w;" << std::endl
		<< "}" << std::endl
		<< "vec3 getEyePosition(vec2 texCoord){"
		<< "	float depth = getDepth(texCoord);" << std::endl
		<< "	return uvToEye(texCoord, depth);" << std::endl
		<< "}" << std::endl
		<< "void main(void) {" << std::endl
		<< "	float depth = getDepth(texCoord);" << std::endl
		<< "	if(depth < 0.01) {" << std::endl
		<< "		discard;" << std::endl
		<< "		return;" << std::endl
		<< "	}" << std::endl
		<< "	vec3 normal = texture2D(normalTex, texCoord).rgb;" << std::endl
		<< "    vec3 position = getEyePosition(texCoord);" << std::endl
		<< "	vec3 worldView = normalize( eyePosition - position );" << std::endl
		<< "	vec3 reflectDir = reflect(-worldView, normal);" << std::endl
		<< "	vec3 refractDir = refract(-worldView, normal, 1.33);" << std::endl
		<< "	vec4 reflectColor = texture(cubeMapTex, reflectDir);" << std::endl
		<< "	vec4 refractColor = texture(cubeMapTex, refractDir);" << std::endl
		<< "	fragColor = mix(refractColor, reflectColor, 1.0);" << std::endl
		<< "}" << std::endl;
	ShaderUnit fragmentShader;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void SSCubeMapRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");

	shader.findUniformLocation("depthTex");
	shader.findUniformLocation("normalTex");
	shader.findUniformLocation("cubeMapTex");

	shader.findUniformLocation("eyePosition");
	shader.findAttribLocation("position");
}

void SSCubeMapRenderer::render(const Crystal::Shader::Texturef& depthTexture, const Crystal::Shader::Texturef& normalTexture, const ICamera<float>& renderedCamera, const CubeMapTexture& cubeMapTexture)
{
	std::vector<float> positions;
	positions.push_back(-1.0f);
	positions.push_back(1.0f);
	positions.push_back(-1.0f);
	positions.push_back(-1.0f);
	positions.push_back(1.0f);
	positions.push_back(-1.0f);
	positions.push_back(1.0f);
	positions.push_back(1.0f);

	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	depthTexture.bind();
	normalTexture.bind();
	cubeMapTexture.bind();

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, renderedCamera.getProjectionMatrix().toArray().data());
	glUniform3fv(shader.getUniformLocation("eyePosition"), 1, renderedCamera.getPosition().toArray3().data());

	glUniform1i(shader.getUniformLocation("depthTex"), depthTexture.getId());
	glUniform1i(shader.getUniformLocation("normalTex"), normalTexture.getId());
	glUniform1i(shader.getUniformLocation("cubeMapTex"), cubeMapTexture.getId());


	glVertexAttribPointer(shader.getAttribLocation("positions"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, positions.size() / 2);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	cubeMapTexture.unbind();
	depthTexture.unbind();
	normalTexture.unbind();
	glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}