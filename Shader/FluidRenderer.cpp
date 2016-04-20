#include "FluidRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void FluidRenderer::build(const int width, const int height)
{
	depthBuffer.build(width, height, 0);
	normalBuffer.build(width, height, 1);
	volumeBuffer.build(width, height, 2);
	bluredBuffer1.build(width, height, 3);
	bluredBuffer2.build(width, height, 4);
	shadedBuffer.build(width, height, 5);
	cubeMapBuffer.build(width, height, 6);
	absorptionBuffer.build(width, height, 7);
	fluidBuffer.build(width, height, 8);
	bluredVolumeBuffer.build(width, height, 9);


	depthRenderer.build();
	normalFilter.build();
	deferredRenderer.build();
	thicknessRenderer.build();
	absorptionRenderer.build();

	bilateralFilter.build();

	cubeMapRenderer.build();

	onScreenRenderer.build();

	const auto vsSource = getBuiltinVertexShaderSource();
	const auto fsSource = getBuiltinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();

}

void FluidRenderer::findLocation()
{
	shader.findUniformLocation("surfaceTexture");
	shader.findUniformLocation("cubeMapTexture");
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
		<< "uniform sampler2D cubeMapTexture;" << std::endl
		<< "uniform sampler2D absorptionTexture;" << std::endl
		<< "uniform sampler2D backgroundTexture;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	vec4 surfaceColor = texture2D(surfaceTexture, texCoord);" << std::endl
		<< "	vec4 cubeMapColor = texture2D(cubeMapTexture, texCoord);" << std::endl
		<< "	vec4 absorptionColor = texture2D(absorptionTexture, texCoord);" << std::endl
		<< "	vec4 bgColor = texture2D(backgroundTexture, texCoord); " << std::endl
		<< "	if(absorptionColor.a < 0.01) { " << std::endl
		<< "		vec4 bgColor = texture2D(backgroundTexture, texCoord); " << std::endl
		<< "		fragColor = bgColor; " << std::endl
		<< "	}else {" << std::endl
		<< "		fragColor = mix(surfaceColor + cubeMapColor,absorptionColor ,absorptionColor.a); " << std::endl
//		<< "		fragColor = surfaceColor*0.5 + cubeMapColor*0.5 + absorptionColor;" << std::endl
//		<< "		fragColor = mix(bgColor, fragColor, absorptionColor.a); "<< std::endl
//		<< "		fragColor.a = absorptionColor.a; " << std::endl
		<< "	}" << std::endl
		<< "}" << std::endl;
	ShaderUnit fragmentShader;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}


void FluidRenderer::render(const int width, const int height, const ICamera<float>& camera, const PointBuffer& buffer, const PointLight<float>& light, const Material& material, const CubeMapTexture& cubeMapTexture, const Texturef& backgroundTexture)
{
	glViewport(0, 0, depthBuffer.getWidth(), depthBuffer.getHeight());
	depthBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	depthRenderer.render(camera, buffer);
	depthBuffer.unbind();

	glViewport(0, 0, bluredBuffer1.getWidth(), bluredBuffer1.getHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bluredBuffer1.bind();
	bilateralFilter.render(*depthBuffer.getTexture(), true);
	bluredBuffer1.unbind();

	/*
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bluredBuffer2.bind();
	bilateralFilter.render(*bluredBuffer1.getTexture(), false);
	bluredBuffer2.unbind();
	*/

	glViewport(0, 0, normalBuffer.getWidth(), normalBuffer.getHeight());
	normalBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	normalFilter.render(*bluredBuffer2.getTexture(), camera);
	normalBuffer.unbind();

	glViewport(0, 0, bluredBuffer1.getWidth(), bluredBuffer1.getHeight());//depthBuffer.getWidth(), depthBuffer.getHeight());
	shadedBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	deferredRenderer.render(*bluredBuffer1.getTexture(), *normalBuffer.getTexture(), camera, light, material);
	shadedBuffer.unbind();

	glViewport(0, 0, cubeMapBuffer.getWidth(), cubeMapBuffer.getHeight());
	cubeMapBuffer.bind();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cubeMapRenderer.render(*bluredBuffer1.getTexture(), *normalBuffer.getTexture(), camera, cubeMapTexture);
	cubeMapBuffer.unbind();

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
	bilateralFilter.render(*volumeBuffer.getTexture(), true);
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


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

		//glEnable(GL_DEPTH_TEST);

		glUseProgram(shader.getId());

		shadedBuffer.getTexture()->bind();
		cubeMapBuffer.getTexture()->bind();
		absorptionBuffer.getTexture()->bind();
		backgroundTexture.bind();

		glUniform1i(shader.getUniformLocation("surfaceTexture"), shadedBuffer.getTexture()->getId());
		glUniform1i(shader.getUniformLocation("cubeMapTexture"), cubeMapBuffer.getTexture()->getId());
		glUniform1i(shader.getUniformLocation("absorptionTexture"), absorptionBuffer.getTexture()->getId());
		glUniform1i(shader.getUniformLocation("backgroundTexture"), backgroundTexture.getId());

		glVertexAttribPointer(shader.getAttribLocation("positions"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

		glEnableVertexAttribArray(0);
		glDrawArrays(GL_QUADS, 0, positions.size() / 2);
		glDisableVertexAttribArray(0);

		glBindFragDataLocation(shader.getId(), 0, "fragColor");

		shadedBuffer.getTexture()->unbind();
		cubeMapBuffer.getTexture()->unbind();
		absorptionBuffer.getTexture()->unbind();
		backgroundTexture.unbind();
	}
	glDisable(GL_BLEND);

	fluidBuffer.unbind();
	glViewport(0, 0, width, height);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	onScreenRenderer.render(*fluidBuffer.getTexture());
}
