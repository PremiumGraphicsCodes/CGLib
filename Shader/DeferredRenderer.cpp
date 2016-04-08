#include "DeferredRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool DeferredRenderer::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string DeferredRenderer::getBuildinVertexShaderSource()
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

std::string DeferredRenderer::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform sampler2D depthTex;" << std::endl
		<< "uniform sampler2D normalTex;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "float getDepth(vec2 tCoord){" << std::endl
		<< "	return texture2D(depthTex, tCoord).r;" << std::endl
		<< "}" << std::endl
//		<< "vec3 getPhongShaded( vec3 position, vec3 normal) {"
//		<< "	vec3 s = normalize(vec3(light.position - position);" << std::endl
//		<< "	vec3 v = normalize(-position.xyz);" << std::endl
//		<< "}"
		<< "void main(void) {" << std::endl
		<< "	float depth = getDepth(texCoord);" << std::endl
		<< "	if(depth < 0.1) {" << std::endl
		<< "		fragColor.rgba = vec4(0.0, 0.0, 0.0, 1.0);" << std::endl
		<< "		return;" << std::endl
		<< "	}" << std::endl
		<< "    vec3 light = vec3(1.0, 0.0, 0.0);" << std::endl
		<< "	vec3 materialColor = vec3(0.0, 0.0, 1.0);" << std::endl
		<< "	vec3 normal = texture2D(normalTex, texCoord).rgb;" << std::endl
		//<< "	vec3 lightPosition = get" << std::endl
		<< "	fragColor.rgb = materialColor * (dot(normal, light)*0.5 + 0.5);" << std::endl
		<< "	fragColor.a = 1.0;" << std::endl
		<< "	}" << std::endl;
	ShaderUnit fragmentShader;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void DeferredRenderer::findLocation()
{
	shader.findUniformLocation("depthTex");
	shader.findUniformLocation("normalTex");

	shader.findAttribLocation("position");
}

void DeferredRenderer::render(const Texture<unsigned char>& depthTexture, const Texture<unsigned char>& normalTexture)
{
	/*
	const std::array<Vector2d<float>, 3> positions = {
	Vector2d<float>(-0.5f, 0.5f),
	Vector2d<float>(-0.5f, -0.5f),
	Vector2d<float>(0.5f, -0.5f)//,
	//Vector3d<float>(0.5f, 0.5f, 0.0f),
	};
	*/
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

	//glGetUniformLocation( texture.getId()
	glUniform1i(shader.getUniformLocation("depthTex"), 0);
	glUniform1i(shader.getUniformLocation("normalTex"), 1);

	glVertexAttribPointer(shader.getAttribLocation("positions"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, positions.size() / 2);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	depthTexture.unbind();
	normalTexture.unbind();
	glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}