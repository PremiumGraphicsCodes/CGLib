#include "DeferredRenderer.h"
#include "../Math/Box2d.h"

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
		<< "uniform mat4 projectionMatrix;" << std::endl
		<< "uniform vec3 eyePosition;" << std::endl
		<< "uniform sampler2D depthTex;" << std::endl
		<< "uniform sampler2D normalTex;" << std::endl
		<< "struct LightInfo {" << std::endl
		<< "	vec3 position;" << std::endl
		<< "	vec3 La;" << std::endl
		<< "	vec3 Ld;" << std::endl
		<< "	vec3 Ls;" << std::endl
		<< "};"
		<< "uniform LightInfo light;"
		<< "struct MaterialInfo {" << std::endl
		<< "	vec3 Ka;" << std::endl
		<< "	vec3 Kd;" << std::endl
		<< "	vec3 Ks;" << std::endl
		<< "	float shininess;" << std::endl
		<< "};"
		<< "uniform MaterialInfo material;"
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
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
		<< "vec3 getPhongShadedColor( vec3 position, vec3 normal) {"
		<< "	vec3 s = normalize(light.position - position);" << std::endl
		<< "	vec3 v = normalize(position - eyePosition);" << std::endl
		<< "	vec3 r = reflect( -s, normal );" << std::endl
		<< "	vec3 ambient = light.La * material.Ka;" << std::endl
		<< "	float innerProduct = max( dot(s,normal), 0.0);" << std::endl
		<< "	vec3 diffuse = light.Ld * material.Kd * innerProduct;" << std::endl
		<< "	vec3 specular = vec3(0.0);" << std::endl
		<< "	if(innerProduct > 0.0) {" << std::endl
		<< "		specular = light.Ls * material.Ks * pow( max( dot(r,v), 0.0 ), material.shininess );" << std::endl
		<< "	}" << std::endl
		<< "	return ambient + diffuse + specular;" << std::endl
		<< "}"
		<< "void main(void) {" << std::endl
		<< "	float depth = getDepth(texCoord);" << std::endl
		<< "	if(depth < 0.01) {" << std::endl
		<< "		fragColor = vec4(0.0, 0.0, 0.0, 0.0);" << std::endl
		<< "		return;" << std::endl
		<< "	}" << std::endl
		<< "	vec3 normal = texture2D(normalTex, texCoord).rgb;" << std::endl
		<< "    vec3 eyePosition = getEyePosition(texCoord);" << std::endl
		<< "	fragColor.rgb = getPhongShadedColor( eyePosition, normal);" << std::endl
		<< "	fragColor.a = 1.0;" << std::endl
		<< "	}" << std::endl;
	ShaderUnit fragmentShader;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void DeferredRenderer::findLocation()
{
	shader.findUniformLocation("projectionMatrix");

	shader.findUniformLocation("depthTex");
	shader.findUniformLocation("normalTex");

	shader.findUniformLocation("light.position");
	shader.findUniformLocation("light.La");
	shader.findUniformLocation("light.Ld");
	shader.findUniformLocation("light.Ls");

	shader.findUniformLocation("material.Ka");
	shader.findUniformLocation("material.Kd");
	shader.findUniformLocation("material.Ks");
	shader.findUniformLocation("material.shininess");

	shader.findUniformLocation("eyePosition");

	shader.findAttribLocation("position");
}

void DeferredRenderer::render(const ITextureObject& depthTexture, const ITextureObject& normalTexture, const ICamera<float>& renderedCamera, const PointLight<float>& light, const Material& material)
{
	const Box2d<float> box(Vector2d<float>(-1.0, -1.0), Vector2d<float>(1.0, 1.0));
	const auto& positions = box.toArray();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	depthTexture.bind();
	normalTexture.bind();

	glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, renderedCamera.getProjectionMatrix().toArray().data());
	glUniform3fv(shader.getUniformLocation("eyePosition"),1, renderedCamera.getPosition().toArray3().data());

	glUniform1i(shader.getUniformLocation("depthTex"), depthTexture.getId());
	glUniform1i(shader.getUniformLocation("normalTex"), normalTexture.getId());

	glUniform3fv(shader.getUniformLocation("light.position"), 1, light.getPos().toArray3().data() );
	glUniform3fv(shader.getUniformLocation("light.La"), 1, light.getAmbient().toArray3().data());
	glUniform3fv(shader.getUniformLocation("light.Ld"), 1, light.getDiffuse().toArray3().data());
	glUniform3fv(shader.getUniformLocation("light.Ls"), 1, light.getSpecular().toArray3().data());

	glUniform3fv(shader.getUniformLocation("material.Ka"), 1, material.getAmbient().toArray3().data() );
	glUniform3fv(shader.getUniformLocation("material.Kd"), 1, material.getDiffuse().toArray3().data() );
	glUniform3fv(shader.getUniformLocation("material.Ks"), 1, material.getSpecular().toArray3().data());
	glUniform1f(shader.getUniformLocation("material.shininess"), material.getShininess());


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