#include "SmoothRenderer.h"
#include "../Graphics/Material.h"
#include "../Graphics/VisualPolygon.h"
#include "VisualMaterial.h"
#include <sstream>

#include "ShaderHandler.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

namespace {
	std::string shaderName = "smooth";
}

bool SmoothRenderer::build()
{
	const auto& vShader = getBuildinVertexShaderSource();
	const auto& fShader = getBuildinFragmentShaderSource();

	bool result = ShaderHandler::getInstance()->build(shaderName, vShader, fShader);
	set(ShaderHandler::getInstance()->get(shaderName));
	
	return result;
}

std::string SmoothRenderer::getBuildinVertexShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 position;" << std::endl
		<< "in vec3 normal;" << std::endl
		<< "in vec3 texCoord;" << std::endl
		<< "out vec3 vNormal;" << std::endl
		<< "out vec3 vTexCoord;" << std::endl
		<< "uniform mat4 projectionMatrix;"
		<< "uniform mat4 modelviewMatrix;"
		<< "void main(void) {" << std::endl
		<< "	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl
		<< "	vNormal = normalize(normal);" << std::endl
		<< "	vTexCoord = texCoord;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}

std::string SmoothRenderer::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "in vec3 vNormal;" << std::endl
		<< "in vec3 vTexCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "uniform vec3 eyePosition;" << std::endl
		<< "uniform sampler2D diffuseTex;" << std::endl
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
		<< "vec3 getPhongShadedColor( vec3 position, vec3 normal) {"
		<< "	vec3 s = normalize(light.position - position);" << std::endl
		<< "	vec3 v = normalize(position - eyePosition);" << std::endl
		<< "	vec3 r = reflect( -s, normal );" << std::endl
		<< "	vec3 ambient = light.La * material.Ka;" << std::endl
		<< "	float innerProduct = max( dot(s,normal), 0.0);" << std::endl
		<< "	vec4 texDiffuse = texture(diffuseTex, vTexCoord.rg);" << std::endl
		<< "	vec3 diffuse = light.Ld * material.Kd * innerProduct * texDiffuse.rgb;" << std::endl
		<< "	vec3 specular = vec3(0.0);" << std::endl
		<< "	if(innerProduct > 0.0) {" << std::endl
		<< "		specular = light.Ls * material.Ks * pow( max( dot(r,v), 0.0 ), material.shininess );" << std::endl
		<< "	}" << std::endl
		<< "	return ambient + diffuse + specular;" << std::endl
		<< "}"
		<< "void main(void) {" << std::endl
		<< "	fragColor.rgb = getPhongShadedColor( eyePosition, vNormal);" << std::endl
		<< "	fragColor.a = 1.0;" << std::endl
		<< "}" << std::endl;
	return stream.str();
}


void SmoothRenderer::set(ShaderObject* shader)
{
	this->shader = shader;
	shader->findUniformLocation("projectionMatrix");
	shader->findUniformLocation("modelviewMatrix");
	shader->findUniformLocation("eyePosition");
	shader->findUniformLocation("light.position");
	shader->findUniformLocation("light.La");
	shader->findUniformLocation("light.Ld");
	shader->findUniformLocation("light.Ls");
	shader->findUniformLocation("material.Ka");
	shader->findUniformLocation("material.Kd");
	shader->findUniformLocation("material.Ks");
	shader->findUniformLocation("material.shininess");
	shader->findUniformLocation("diffuseTex");

	shader->findAttribLocation("position");
	shader->findAttribLocation("normal");
	shader->findAttribLocation("texCoord");
}


void SmoothRenderer::render(const ICamera<float>& camera, const TriangleBuffer& buffer, const PointLight<float>& light, const Material& material)
{
	const auto& indices = buffer.getIndices();
	const auto& positions = buffer.getPositions().get();// buffers[0].get();
	const auto& normals = buffer.getNormals().get();//buffers[1].get();
	if (positions.empty()) {
		return;
	}

	glEnable(GL_DEPTH_TEST);

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();
	const auto& eyePos = camera.getPosition().toArray();

	assert(GL_NO_ERROR == glGetError());

	glUseProgram(shader->getId());

	const auto& lightPos = light.getPos().toArray();//{ -10.0f, 10.0f, 10.0f };

	glUniform3fv(shader->getUniformLocation("light.position"), 1, light.getPos().toArray3().data());
	glUniform3fv(shader->getUniformLocation("light.La"), 1, light.getAmbient().toArray3().data());
	glUniform3fv(shader->getUniformLocation("light.Ld"), 1, light.getDiffuse().toArray3().data());
	glUniform3fv(shader->getUniformLocation("light.Ls"), 1, light.getSpecular().toArray3().data());

	glUniform3fv(shader->getUniformLocation("material.Ka"), 1, material.getAmbient().toArray3().data());
	glUniform3fv(shader->getUniformLocation("material.Kd"), 1, material.getDiffuse().toArray3().data());
	glUniform3fv(shader->getUniformLocation("material.Ks"), 1, material.getSpecular().toArray3().data());
	glUniform1f(shader->getUniformLocation("material.shininess"), material.getShininess());

	glBindFragDataLocation(shader->getId(), 0, "fragColor");

	glUniformMatrix4fv(shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader->getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());
	glUniform3fv(shader->getUniformLocation("eyePosition"), 1, eyePos.data());

	assert(GL_NO_ERROR == glGetError());

	glVertexAttribPointer(shader->getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader->getAttribLocation("normal"), 3, GL_FLOAT, GL_FALSE, 0, normals.data());
	//glVertexAttribPointer(location.)
	assert(GL_NO_ERROR == glGetError());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	assert(GL_NO_ERROR == glGetError());


	//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size() / 3));
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	glUseProgram(0);

	const GLenum error = glGetError();
	assert(GL_NO_ERROR == error);

	glDisable(GL_DEPTH_TEST);
}

void SmoothRenderer::render(const ICamera<float>& camera, const TriangleBuffer& buffer, const PointLight<float>& light, const std::vector<VisualMaterial>& materials)
{
	const auto& positions = buffer.getPositions().get();// buffers[0].get();
	const auto& normals = buffer.getNormals().get();//buffers[1].get();
	const auto& texCoords = buffer.getTexCoords().get();
	if (positions.empty()) {
		return;
	}

	glEnable(GL_DEPTH_TEST);

	const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
	const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();
	const auto& eyePos = camera.getPosition().toArray();

	assert(GL_NO_ERROR == glGetError());

	glUseProgram(shader->getId());

	const auto& lightPos = light.getPos().toArray();//{ -10.0f, 10.0f, 10.0f };

	const auto lightLoc = glGetUniformLocation(shader->getId(), "light.position");
	glUniform3fv(lightLoc, 1, lightPos.data());

	glBindFragDataLocation(shader->getId(), 0, "fragColor");

	glUniformMatrix4fv(shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
	glUniformMatrix4fv(shader->getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());
	glUniform3fv(shader->getUniformLocation("eyePosition"), 1, eyePos.data());

	assert(GL_NO_ERROR == glGetError());

	glUniform3fv(shader->getUniformLocation("light.position"), 1, light.getPos().toArray3().data());
	glUniform3fv(shader->getUniformLocation("light.La"), 1, light.getAmbient().toArray3().data());
	glUniform3fv(shader->getUniformLocation("light.Ld"), 1, light.getDiffuse().toArray3().data());
	glUniform3fv(shader->getUniformLocation("light.Ls"), 1, light.getSpecular().toArray3().data());



	glVertexAttribPointer(shader->getAttribLocation("position"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
	glVertexAttribPointer(shader->getAttribLocation("normal"), 3, GL_FLOAT, GL_FALSE, 0, normals.data());
	glVertexAttribPointer(shader->getAttribLocation("texCoord"), 3, GL_FLOAT, GL_FALSE, 0, texCoords.data());

	//glVertexAttribPointer(location.)
	assert(GL_NO_ERROR == glGetError());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	assert(GL_NO_ERROR == glGetError());

	for (auto& m : materials) {
		const auto indices = buffer.getIndices(m.getStartFaceIndex(), m.getEndFaceIndex());
		const auto diffuseTex = m.getDiffuseTex();
		diffuseTex.bind();

		glUniform3fv(shader->getUniformLocation("material.Ka"), 1, m.getAmbientColor().data());
		glUniform3fv(shader->getUniformLocation("material.Kd"), 1, m.getDiffuseColor().data());
		glUniform3fv(shader->getUniformLocation("material.Ks"), 1, m.getSpecularColor().data());
		glUniform1f(shader->getUniformLocation("material.shininess"), m.getShininess());
		glUniform1i(shader->getUniformLocation("diffuseTex"), diffuseTex.getId());


		//glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size() / 3));
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

		diffuseTex.unbind();
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);


	glUseProgram(0);

	const GLenum error = glGetError();
	assert(GL_NO_ERROR == error);

	glDisable(GL_DEPTH_TEST);
}
