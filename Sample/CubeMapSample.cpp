#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"
#include "CubeMapSample.h"

#include <iostream>

#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;


CubeMapSample::CubeMapSample()
{
}




void CubeMapSample::setup()
{
	Crystal::Graphics::Image<float> image(2, 2);
	image.setColor(0, 0, ColorRGBA<float>(0.0, 0.0, 1.0, 1.0));
	image.setColor(1, 1, ColorRGBA<float>(0.0, 0.0, 1.0, 1.0));
	cubeMapTexture.create(image, 10);

	renderer.build();
	//renderer.build(512, 512);

	polygon.add(Crystal::Math::Box3d<float>(Crystal::Math::Vector3d<float>(0.0, 0.0, 0.0), Crystal::Math::Vector3d<float>(1.0, 1.0, 1.0)));
	//buffer.add(Triangle<float>(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(1.0f, 0.0, 0.0), Vector3d<float>(1.0f, 1.0f, 0.0)));
}

void CubeMapSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	Crystal::Graphics::TriangleBuffer buffer;
	buffer.add(polygon);

	renderer.render(cubeMapTexture, camera, buffer);
}
