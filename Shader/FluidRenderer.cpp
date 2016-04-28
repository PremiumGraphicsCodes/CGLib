#include "FluidRenderer.h"
#include "../Math/Box2d.h"
#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void FluidRenderer::build(const int width, const int height)
{
	depthTexture.create(Imagef(width, height), 0);
	depthBuffer.build(depthTexture);

	shadedTexture.create(Image(width, height), 1);
	bluredDepthTexture.create(Image(width, height), 2);
	normalTexture.create(Image(width, height), 3);
	thicknessTexture.create(Image(width, height), 4);
	bluredThicknessTexture.create(Image(width, height), 5);
	volumeTexture.create(Image(width, height), 6);
	sceneTexture.create(Image(width, height), 7);
	reflectionTexture.create(Image(width, height), 8);
	fluidTexture.create(Image(width, height), 9);

	depthRenderer.build();
	normalFilter.build();
	deferredRenderer.build();
	thicknessRenderer.build();
	absorptionRenderer.build();

	bilateralFilter.build();

	reflectionRenderer.build();
	refractionRenderer.build();

	frameBuffer.build(512, 512);

	onScreenRenderer.build();

	const auto vsSource = getBuiltinVertexShaderSource();
	const auto fsSource = getBuiltinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();

}

void FluidRenderer::findLocation()
{
	shader.findUniformLocation("surfaceTexture");
	shader.findUniformLocation("reflectionTexture");
	//shader.findUniformLocation("refractionTexture");

	shader.findUniformLocation("absorptionTexture");
	shader.findUniformLocation("backgroundTexture");

	shader.findAttribLocation("position");
}

std::string FluidRenderer::getBuiltinVertexShaderSource()
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

std::string FluidRenderer::getBuiltinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform sampler2D surfaceTexture;" << std::endl
		<< "uniform sampler2D reflectionTexture;" << std::endl
		//<< "uniform sampler2D refractionTexture;" << std::endl
		<< "uniform sampler2D absorptionTexture;" << std::endl
		<< "uniform sampler2D backgroundTexture;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	vec4 surfaceColor = texture2D(surfaceTexture, texCoord);" << std::endl
		<< "	vec4 reflectionColor = texture2D(reflectionTexture, texCoord);" << std::endl
		//<< "	vec4 refractionColor = texture2D(refractionTexture, texCoord);" << std::endl
		<< "	vec4 absorptionColor = texture2D(absorptionTexture, texCoord);" << std::endl
		<< "	vec4 bgColor = texture2D(backgroundTexture, texCoord);" << std::endl
		<< "	if(absorptionColor.a < 0.01) { " << std::endl
		<< "		fragColor = bgColor;" << std::endl
		<< "		return; " << std::endl
		<< "	}else {" << std::endl
		<< "		fragColor = mix( absorptionColor, surfaceColor + reflectionColor, 1.0-absorptionColor.a);" << std::endl
		<< "	}" << std::endl
		<< "}" << std::endl;
	ShaderUnit fragmentShader;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}


void FluidRenderer::render(const int width, const int height, const ICamera<float>& camera, const PointBuffer& buffer, const PointLight<float>& light, const Material& material, const CubeMapTexture& cubeMapTexture)
{
	depthBuffer.setTexture(depthTexture);
	glViewport(0, 0, depthBuffer.getWidth(), depthBuffer.getHeight());
	depthBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	depthRenderer.render(camera, buffer);
	depthBuffer.unbind();

	frameBuffer.setTexture(bluredDepthTexture);
	glViewport(0, 0, bluredDepthTexture.getWidth(), bluredDepthTexture.getHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	frameBuffer.bind();
	bilateralFilter.render(depthTexture);
	frameBuffer.unbind();

	frameBuffer.setTexture(normalTexture);
	glViewport(0, 0, normalTexture.getWidth(), normalTexture.getHeight());
	frameBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	normalFilter.render(bluredDepthTexture, camera);
	frameBuffer.unbind();

	frameBuffer.setTexture(shadedTexture);
	glViewport(0, 0, bluredDepthTexture.getWidth(), bluredDepthTexture.getHeight());//depthBuffer.getWidth(), depthBuffer.getHeight());
	frameBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	deferredRenderer.render(bluredDepthTexture, normalTexture, camera, light, material);
	frameBuffer.unbind();

	frameBuffer.setTexture(reflectionTexture);
	glViewport(0, 0, reflectionTexture.getWidth(), reflectionTexture.getHeight());
	frameBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	reflectionRenderer.render(bluredDepthTexture, normalTexture, camera, cubeMapTexture);
	frameBuffer.unbind();

	frameBuffer.setTexture(thicknessTexture);
	glViewport(0, 0, thicknessTexture.getWidth(), thicknessTexture.getHeight());
	frameBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	thicknessRenderer.render(camera, buffer);
	frameBuffer.unbind();

	frameBuffer.setTexture(bluredThicknessTexture);
	glViewport(0, 0, bluredThicknessTexture.getWidth(), bluredThicknessTexture.getHeight());
	frameBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bilateralFilter.render(thicknessTexture);
	frameBuffer.unbind();

	frameBuffer.setTexture(volumeTexture);
	glViewport(0, 0, volumeTexture.getWidth(), volumeTexture.getHeight());
	frameBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	absorptionRenderer.render(bluredThicknessTexture);
	frameBuffer.unbind();


	frameBuffer.setTexture(fluidTexture);
	glViewport(0, 0, fluidTexture.getWidth(), fluidTexture.getHeight());
	frameBuffer.bind();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	{
		const Box2d<float> box(Vector2d<float>(-1.0, -1.0), Vector2d<float>(1.0, 1.0));
		const auto& positions = box.toArray();

		//glEnable(GL_DEPTH_TEST);

		glUseProgram(shader.getId());

		shadedTexture.bind();
		reflectionTexture.bind();
		volumeTexture.bind();
		sceneTexture.bind();

		glUniform1i(shader.getUniformLocation("surfaceTexture"), shadedTexture.getId());
		glUniform1i(shader.getUniformLocation("reflectionTexture"), reflectionTexture.getId());
		//glUniform1i(shader.getUniformLocation("refractionTexture"), refractionBuffer.getTexture()->getId());

		glUniform1i(shader.getUniformLocation("absorptionTexture"), volumeTexture.getId());
		glUniform1i(shader.getUniformLocation("backgroundTexture"), sceneTexture.getId());

		glVertexAttribPointer(shader.getAttribLocation("positions"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

		glEnableVertexAttribArray(0);
		glDrawArrays(GL_QUADS, 0, positions.size() / 2);
		glDisableVertexAttribArray(0);

		glBindFragDataLocation(shader.getId(), 0, "fragColor");

		shadedTexture.unbind();
		reflectionTexture.unbind();
		volumeTexture.unbind();
		sceneTexture.unbind();
	}

	frameBuffer.unbind();

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	onScreenRenderer.render(fluidTexture);
}
