#include "SSAbsorptionRenderer.h"
#include "../Math/Box2d.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool SSAbsorptionRenderer::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string SSAbsorptionRenderer::getBuildinVertexShaderSource()
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

std::string SSAbsorptionRenderer::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform sampler2D volumeTex;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	float volume = texture2D(volumeTex, texCoord).a;" << std::endl
		<< "	if(volume < 0.01 ) {" << std::endl
		<< "		fragColor.rgb = vec3(0.0, 0.0, 0.0);" << std::endl
		<< "		fragColor.a = 0.0;" << std::endl
		<< "		return;" << std::endl
		<< "	}" << std::endl
		<< "	float k = 0.1;" << std::endl
		<< "	fragColor.rgb = exp(-k*volume) * vec3(5/255.0, 102/255.0, 255/255.0);" << std::endl
		//<< "	fragColor.rgb += vec3(0.0, 0.0, 0.0);" << std::endl
		<< "	fragColor.a = volume;" << std::endl
		<< "}" << std::endl;
	ShaderUnit fragmentShader;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void SSAbsorptionRenderer::findLocation()
{
	shader.findUniformLocation("volumeTex");
	shader.findAttribLocation("position");
}

void SSAbsorptionRenderer::render(const ITextureObject& volumeTexture)
{
	const Box2d<float> box(Vector2d<float>(-1.0, -1.0), Vector2d<float>(1.0, 1.0));
	const auto& positions = box.toArray();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glEnable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.getId());

	volumeTexture.bind();

	glUniform1i(shader.getUniformLocation("volumeTex"), volumeTexture.getId());// volumeTexture.getId());

	glVertexAttribPointer(shader.getAttribLocation("positions"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_QUADS, 0, static_cast<GLsizei>( positions.size() / 2) );
	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	volumeTexture.unbind();
	glDisable(GL_DEPTH_TEST);

	//glDisable(GL_BLEND);


	glUseProgram(0);
}