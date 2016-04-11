#include "AbsorptionRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool AbsorptionRenderer::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string AbsorptionRenderer::getBuildinVertexShaderSource()
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

std::string AbsorptionRenderer::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform sampler2D volumeTex;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	float volume = texture2D(volumeTex, texCoord).r;" << std::endl
		<< "	if(volume < 0.10 ) {" << std::endl
		<< "		fragColor.rgb = vec3(0.0, 0.0, 0.0);" << std::endl
		<< "		fragColor.a = 1.0;" << std::endl
		<< "		return;" << std::endl
		<< "	}" << std::endl
		<< "	float k = 1.0;" << std::endl
		<< "	fragColor.rgb = exp(-k*volume) * vec3(0.0, 0.0, 1.0);" << std::endl
		<< "	fragColor.a = 1.0;" << std::endl
		<< "}" << std::endl;
	ShaderUnit fragmentShader;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void AbsorptionRenderer::findLocation()
{
	shader.findUniformLocation("volumeTex");
	shader.findAttribLocation("position");
}

void AbsorptionRenderer::render(const Texture<unsigned char>& volumeTexture)
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

	glUseProgram(shader.getId());

	volumeTexture.bind();

	glUniform1i(shader.getUniformLocation("volumeTex"), 2);// volumeTexture.getId());

	glVertexAttribPointer(shader.getAttribLocation("positions"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, positions.size() / 2);
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	volumeTexture.unbind();
	glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}