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
	Crystal::Graphics::Imagef image1;
	image1.read("../Shader/cube_PX.png");
	Crystal::Graphics::Imagef image2;
	image2.read("../Shader/cube_NX.png");
	Crystal::Graphics::Imagef image3;
	image3.read("../Shader/cube_PY.png");
	Crystal::Graphics::Imagef image4;
	image4.read("../Shader/cube_NY.png");
	Crystal::Graphics::Imagef image5;
	image5.read("../Shader/cube_PZ.png");
	Crystal::Graphics::Imagef image6;
	image6.read("../Shader/cube_NZ.png");

	cubeMapTexture.create(image1, 10);
	cubeMapTexture.setNegativeX(image2);
	cubeMapTexture.setPositiveY(image3);
	cubeMapTexture.setNegativeY(image4);
	cubeMapTexture.setPositiveZ(image5);
	cubeMapTexture.setNegativeZ(image6);

	renderer.build();
	skyBoxRenderer.build();
	//renderer.build(512, 512);

	{
		//Triangle<float> triangle1(Vector3d<float>(-10.0, -10.0, 0.0), Vector3d<float>(10.0, -10.0, 0.0), Vector3d<float>(10.0, 10.0, 0.0));
		//Triangle<float> triangle2(Vector3d<float>(-10.0, -10.0, 0.0), Vector3d<float>(10.0, 10.0, 0.0), Vector3d<float>(-10.0, 10.0, 0.0));

		//polygon.add(triangle1);
		//polygon.add(triangle2);
		Crystal::Math::Box3d<float> box(Crystal::Math::Vector3d<float>(-1.0, -1.0, -1.0), Crystal::Math::Vector3d<float>(1.0, 1.0, 1.0));
		polygon.add(box);
	}

	Crystal::Math::Box3d<float> box(Crystal::Math::Vector3d<float>(-10.0, -10.0, -10.0), Crystal::Math::Vector3d<float>(10.0, 10.0, 10.0));
	skyPolygon.add(box);
	//polygon.add(box);
}

void CubeMapSample::demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	{
		Crystal::Graphics::TriangleBuffer buffer;
		buffer.add(skyPolygon);
		skyBoxRenderer.render(cubeMapTexture, camera, buffer);

	}
	{
		Crystal::Graphics::TriangleBuffer buffer;
		buffer.add(polygon);

		renderer.render(cubeMapTexture, camera, buffer);
	}
}
