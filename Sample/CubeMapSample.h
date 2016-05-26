#ifndef __CRYSTAL_SAMPLE_CUBE_MAP_SAMPLE_H__
#define __CRYSTAL_SAMPLE_CUBE_MAP_SAMPLE_H__

#include "../Shader/GLee.h"
#include "../Shader/FluidRenderer.h"

#include "../Shader/ShaderObject.h"
#include "../Graphics/TriangleBuffer.h"

#include "../Shader/CubeMapTextureObject.h"
#include "../Shader/CubeMapRenderer.h"
#include "../Shader/SkyBoxRenderer.h"

#include "ISample.h"
#include <memory>


class CubeMapSample : public ISample
{
public:
	CubeMapSample();

	void setup() override;

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

	//void onMiddleButtonDown(const float x, const float y) override;

private:
	Crystal::Shader::CubeMapRenderer renderer;
	Crystal::Shader::CubeMapTextureObject cubeMapTexture;
	Crystal::Core::PolygonMesh polygon;
	Crystal::Shader::SkyBoxRenderer skyBoxRenderer;

};

#endif