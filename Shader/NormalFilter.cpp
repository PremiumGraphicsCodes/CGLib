#include "NormalFilter.h"
//
//#include <sstream>
//
//using namespace Crystal::Math;
//using namespace Crystal::Graphics;
//using namespace Crystal::Shader;
//
//bool NormalFilter::build()
//{
//	const auto vsSource = getBuildinVertexShaderSource();
//	const auto fsSource = getBuildinFragmentShaderSource();
//	bool b = shader.build(vsSource, fsSource);
//	findLocation();
//	return b;
//}
//
//std::string NormalFilter::getBuildinVertexShaderSource()
//{
////#version 150
//	// in vec2 pv;
//	// out ve2 tc;
//	// void main(void)
//	//{
//	// tc = pv * 0.5 + 0.5;
//	// gl_Position = vec4(pv, 0.0, 1.0);
//	//}
//
//	std::ostringstream stream;
//	stream << "#version 150" << std::endl;
//	stream << "in vec3 position;" << std::endl;
//	stream << "uniform mat4 projectionMatrix;" << std::endl;
//	stream << "uniform mat4 modelviewMatrix;" << std::endl;
//	stream << "void main(void) {" << std::endl;
//	stream << "gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);" << std::endl;
//	stream << "}" << std::endl;
//	ShaderUnit vertexShader;
//	bool b = vertexShader.compile(stream.str(), ShaderUnit::Stage::VERTEX);
//	return stream.str();
//}
//
//std::string NormalFilter::getBuildinFragmentShaderSource()
//{
//	std::ostringstream stream;
//	stream
//		<< "#version 150" << std::endl
//		<< "vec3 uvToEye(vec2 texCoord, float depth) {" << std::endl
//		<< "	vec2 xy = texCoord*2.0 - vec2(1.0,1.0);" << std::endl
//		<< "	vec4 clippingPosition = vec4(xy, depth, 1.0);" << std::endl
//		<< "	vec4 viewPosition = inverse(projectionMatrix) * clippingPosition;" << std::endl
//		<< "    "
//		<< "uniform sampler2D depthTex" << std::endl
//		<< "out vec4 fragColor;" << std::endl
//		<< "void main(void) {" << std::endl
//		<< "    float eyePosition = uvToEye(texCoord, depth)" << std::endl
//		<< " float wsum = 0;" << std::endl
//		<< "	for(float x = -filterRadius; x <= filterRadius; x+= 1.0){"
//		<< "		float sample = texture(tex, texCoord + x );" << std::endl
//		<< "		float r = x * blurScale;" << std::endl
//		<< "		float w = exp(-r*r);" << std::endl
//		<< "		float r2 = (sample-depth) * blurDepthFalloff;" << std::endl
//		<< "		float g = exp(-r2*r2);" << std::endl;
//stream << "		sum += sample * w * g;" << std::endl;
//stream << "		wsum += w * g;" << std::endl;
//stream << " }" << std::endl;
//stream << "if(wsum > 0.0) {" << std::endl;
//stream << " sum / = wsum;" << std::endl;
//stream << "}" << std::endl;
//stream << "vColor.rgb = vec3(sum);" << std::endl;
//stream << "vColor.a = 1.0;" << std::endl;
//bool b = fragmentShader.compile(stream.str(), ShaderUnit::Stage::FRAGMENT);
//return stream.str();
//}
//
//void BilateralFilter::findLocation()
//{
//shader.findUniformLocation("projectionMatrix");
//shader.findUniformLocation("modelviewMatrix");
//
//shader.findAttribLocation("position");
//shader.findAttribLocation("pointSize");
//}
//
//#include "../Graphics/OrthogonalCamera.h"
//
//void BilateralFilter::render(const Texture<float>& texture)
//{
//OrthogonalCamera<float> camera;
//camera.moveTo(Vector3d<float>(0.0f, 0.0f, -1.0f));
//camera.setNear(0.5f);
//camera.setFar(1.0f);
//
//const auto& projectionMatrix = camera.getProjectionMatrix().toArray();
//const auto& modelviewMatrix = camera.getModelviewMatrix().toArray();
//
//std::array<Vector3d<float>, 4> positions = {
//Vector3d<float>(-0.5f, 0.5f, 0.0f),
//Vector3d<float>(-0.5f, -0.5f, 0.0f),
//Vector3d<float>(0.5f, -0.5f, 0.0f),
//Vector3d<float>(0.5f, 0.5f, 0.0f),
//};
//
//glEnable(GL_DEPTH_TEST);
//
//
//glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
//glEnable(GL_POINT_SPRITE);
//
//
////glEnable(GL_BLEND);
////glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
////glDepthMask(GL_FALSE);
////glEnable(GL_DEPTH_TEST);
//
//glUseProgram(shader.getId());
//
//glUniformMatrix4fv(shader.getUniformLocation("projectionMatrix"), 1, GL_FALSE, projectionMatrix.data());
//glUniformMatrix4fv(shader.getUniformLocation("modelviewMatrix"), 1, GL_FALSE, modelviewMatrix.data());
//
//glVertexAttribPointer(shader.getAttribLocation("positions"), 3, GL_FLOAT, GL_FALSE, 0, positions.data());
//
//
////const auto positions = buffer.getPositions();
//glEnableVertexAttribArray(0);
//
//glDrawArrays(GL_QUADS, 0, positions.size() / 3);
//
//glDisableVertexAttribArray(0);
//
//glBindFragDataLocation(shader.getId(), 0, "fragColor");
//
////glDisable(GL_BLEND);
////glDepthMask(GL_TRUE);
//
//
//glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
//glDisable(GL_POINT_SPRITE);
//
//glDisable(GL_DEPTH_TEST);
//
//glUseProgram(0);
//}
//*/