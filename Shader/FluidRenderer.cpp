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
	normalBuffer.build(width, height, 1);
	volumeBuffer.build(width, height, 2);
	bluredDepthBuffer.build(width, height, 3);
	shadedBuffer.build(width, height, 4);
	refractionBuffer.build(width, height, 5);
	reflectionBuffer.build(width, height, 6);
	absorptionBuffer.build(width, height, 7);
	fluidBuffer.build(width, height, 8);
	bluredVolumeBuffer.build(width, height, 9);
	bluredDepthBuffer2.build(width, height, 10);


	depthRenderer.build();
	normalFilter.build();
	deferredRenderer.build();
	thicknessRenderer.build();
	absorptionRenderer.build();

	bilateralFilter.build();

	reflectionRenderer.build();
	refractionRenderer.build();

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

	glViewport(0, 0, bluredDepthBuffer.getWidth(), bluredDepthBuffer.getHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bluredDepthBuffer.bind();
	bilateralFilter.render(*depthBuffer.getTexture());
	bluredDepthBuffer.unbind();

	glViewport(0, 0, normalBuffer.getWidth(), normalBuffer.getHeight());
	normalBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	normalFilter.render(*bluredDepthBuffer.getTexture(), camera);
	normalBuffer.unbind();

	glViewport(0, 0, bluredDepthBuffer.getWidth(), bluredDepthBuffer.getHeight());//depthBuffer.getWidth(), depthBuffer.getHeight());
	shadedBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	deferredRenderer.render(*bluredDepthBuffer.getTexture(), *normalBuffer.getTexture(), camera, light, material);
	shadedBuffer.unbind();

	glViewport(0, 0, reflectionBuffer.getWidth(), reflectionBuffer.getHeight());
	reflectionBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	reflectionRenderer.render(*bluredDepthBuffer.getTexture(), *normalBuffer.getTexture(), camera, cubeMapTexture);
	reflectionBuffer.unbind();

	/*
	glViewport(0, 0, refractionBuffer.getWidth(), refractionBuffer.getHeight());
	refractionBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	refractionRenderer.render(*bluredDepthBuffer.getTexture(), *normalBuffer.getTexture(), camera, cubeMapTexture);
	refractionBuffer.unbind();
	*/
	//depthBuffer.setTexture(sceneDepthTexture);
	glViewport(0, 0, volumeBuffer.getWidth(), volumeBuffer.getHeight());
	volumeBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	thicknessRenderer.render(camera, buffer);
	volumeBuffer.unbind();

	glViewport(0, 0, volumeBuffer.getWidth(), volumeBuffer.getHeight());
	bluredVolumeBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bilateralFilter.render(*volumeBuffer.getTexture());
	bluredVolumeBuffer.unbind();

	glViewport(0, 0, absorptionBuffer.getWidth(), absorptionBuffer.getHeight());
	absorptionBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	absorptionRenderer.render(*bluredVolumeBuffer.getTexture());
	absorptionBuffer.unbind();


	glViewport(0, 0, fluidBuffer.getWidth(), fluidBuffer.getHeight());
	fluidBuffer.bind();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	{
		const Box2d<float> box(Vector2d<float>(-1.0, -1.0), Vector2d<float>(1.0, 1.0));
		const auto& positions = box.toArray();

		//glEnable(GL_DEPTH_TEST);

		glUseProgram(shader.getId());

		shadedBuffer.getTexture()->bind();
		reflectionBuffer.getTexture()->bind();
		refractionBuffer.getTexture()->bind();
		absorptionBuffer.getTexture()->bind();
		sceneTexture.bind();

		glUniform1i(shader.getUniformLocation("surfaceTexture"), shadedBuffer.getTexture()->getId());
		glUniform1i(shader.getUniformLocation("reflectionTexture"), reflectionBuffer.getTexture()->getId());
		//glUniform1i(shader.getUniformLocation("refractionTexture"), refractionBuffer.getTexture()->getId());

		glUniform1i(shader.getUniformLocation("absorptionTexture"), absorptionBuffer.getTexture()->getId());
		glUniform1i(shader.getUniformLocation("backgroundTexture"), sceneTexture.getId());

		glVertexAttribPointer(shader.getAttribLocation("positions"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

		glEnableVertexAttribArray(0);
		glDrawArrays(GL_QUADS, 0, positions.size() / 2);
		glDisableVertexAttribArray(0);

		glBindFragDataLocation(shader.getId(), 0, "fragColor");

		shadedBuffer.getTexture()->unbind();
		refractionBuffer.getTexture()->unbind();

		reflectionBuffer.getTexture()->unbind();
		absorptionBuffer.getTexture()->unbind();
		sceneTexture.unbind();
	}

	fluidBuffer.unbind();
	glViewport(0, 0, width, height);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	onScreenRenderer.render(*fluidBuffer.getTexture());
}
