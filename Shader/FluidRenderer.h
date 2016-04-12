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

namespace Crystal {
	namespace Shader {

class FluidRenderer
{
public:
	void build();

	void render(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera, const Crystal::Graphics::PointBuffer& buffer);

private:
	ParticleDepthRenderer depthRenderer;
	FrameBufferf depthBuffer;

	NormalFilter normalFilter;
	FrameBufferf normalBuffer;

	PointRenderer pointRenderer;
	FrameBufferf volumeBuffer;

	BilateralFilter bilateralFilter;
	FrameBufferf bluredBuffer1;
	FrameBufferf bluredBuffer2;

	AbsorptionRenderer absorptionRenderer;
	DeferredRenderer deferredRenderer;
	OnScreenRenderer onScreenRenderer;
};

	}
}

#endif