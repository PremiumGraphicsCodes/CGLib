#include "BilateralFilter.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool BilateralFilter::build()
{
	const auto vsSource = getBuildinVertexShaderSource();
	const auto fsSource = getBuildinFragmentShaderSource();
	bool b = shader.build(vsSource, fsSource);
	findLocation();
	return b;
}

std::string BilateralFilter::getBuildinVertexShaderSource()
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
	bool b = vertexShader.compile(stream.str(), ShaderUnit::Stage::VERTEX);
	return stream.str();
}

std::string BilateralFilter::getBuildinFragmentShaderSource()
{
	std::ostringstream stream;
	stream
		<< "#version 150" << std::endl
		<< "uniform sampler2D tex;" << std::endl
		<< "in vec2 texCoord;" << std::endl
		<< "out vec4 fragColor;" << std::endl
		<< "void main(void) {" << std::endl
		<< "	float sum = 0;" << std::endl
		<< "	float wsum = 0;" << std::endl
		<< "	float filterRadius = 20;" << std::endl
		<< "	float blurScale = 30;" << std::endl
		<< "	float blurDepthFalloff = 0.1;" << std::endl
		<< "	float depth = texture2D(tex, texCoord).r;" << std::endl
		<< "	for(float x = -filterRadius; x <= filterRadius; x+= 1.0){" << std::endl
		<< "		float sample = texture2D(tex, texCoord + x/512.0 ).r;" << std::endl
		<< "		float r = x/512.0 * blurScale;" << std::endl
		<< "		float w = exp(-r*r);" << std::endl
		<< "		float r2 = (sample-depth) * blurDepthFalloff;" << std::endl
		<< "		float g = exp(-r2*r2);" << std::endl
		<< "		sum += sample * w * g;" << std::endl
		<< "		wsum += w * g;" << std::endl
		<< "	}" << std::endl
		<< "	if(wsum > 0.0) {" << std::endl
		<< "		sum /= wsum;" << std::endl
		<< "	}" << std::endl
		<< "	fragColor.rgb = vec3(sum);" << std::endl
	//	<< "	fragColor.rg = texCoord.rg;" << std::endl
		<< "	fragColor.a = 1.0;" << std::endl
		<< "}" << std::endl;
	bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
	return stream.str();
}

void BilateralFilter::findLocation()
{
	shader.findAttribLocation("position");
}

#include "../Graphics/OrthogonalCamera.h"

void BilateralFilter::render(const Texture<unsigned char>& texture)
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

	glVertexAttribPointer(shader.getAttribLocation("positions"), 2, GL_FLOAT, GL_FALSE, 0, positions.data());

	texture.bind();
	glUniform1i(shader.getUniformLocation("tex"), texture.getId());

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_QUADS, 0, positions.size() / 2);

	glDisableVertexAttribArray(0);

	glBindFragDataLocation(shader.getId(), 0, "fragColor");

	texture.unbind();

	glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
}