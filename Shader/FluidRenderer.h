#ifndef __CRYSTAL_SHADER_FLUID_RENDERER_H__
#define __CRYSTAL_SHADER_FLUID_RENDERER_H__

#include "ParticleDepthRenderer.h"
#include "FrameBuffer.h"
#include "NormalFilter.h"
#include "PointRenderer.h"
#include "BilateralFilter.h"
#include "AbsorptionRenderer.h"
#include "DeferredRenderer.h"
#include "OnScreenRenderer.h"
#include "CubeMapTexture.h"
#include "SSCubeMapRenderer.h"
#include "SkyBoxRenderer.h"
#include "ThicknessRenderer.h"

namespace Crystal {
	namespace Shader {

class FluidRenderer
{
public:
	void build(const int width, const int height);

	void render(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera, const Crystal::Graphics::PointBuffer& buffer);

private:
	ParticleDepthRenderer depthRenderer;
	FrameBufferf depthBuffer;

	NormalFilter normalFilter;
	FrameBufferf normalBuffer;

	ThicknessRenderer thicknessRenderer;
	FrameBufferf volumeBuffer;
	FrameBufferf bluredVolumeBuffer;

	FrameBufferf shadedBuffer;
	
	BilateralFilter bilateralFilter;
	FrameBufferf bluredBuffer1;
	FrameBufferf bluredBuffer2;

	AbsorptionRenderer absorptionRenderer;
	FrameBufferf absorptionBuffer;

	DeferredRenderer deferredRenderer;
	OnScreenRenderer onScreenRenderer;
	CubeMapTexture cubeMapTexture;
	SSCubeMapRenderer cubeMapRenderer;
	FrameBufferf cubeMapBuffer;

	SkyBoxRenderer skyBoxRenderer;

	FrameBufferf fluidBuffer;

private:
	std::string getBuiltinVertexShaderSource();

	std::string getBuiltinFragmentShaderSource();

	void findLocation();

	ShaderObject shader;
};

	}
}

#endif