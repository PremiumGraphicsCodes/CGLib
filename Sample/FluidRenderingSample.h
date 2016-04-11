#ifndef __CRYSTAL_SAMPLE_FLUID_RENDERER_SAMPLE_H__
#define __CRYSTAL_SAMPLE_FLUID_RENDERER_SAMPLE_H__

#include "../Shader/GLee.h"
#include "../Shader/ParticleDepthRenderer.h"
#include "../Shader/NormalFilter.h"
#include "../Shader/FrameBuffer.h"
#include "../Shader/DeferredRenderer.h"
#include "../Shader/PointRenderer.h"
#include "../Shader/AbsorptionRenderer.h"
#include "../Shader/BilateralFilter.h"

#include "ISample.h"
#include <memory>

class FluidRendererSample : public ISample
{
public:
	FluidRendererSample();

	void setup() override;

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

	//void onMiddleButtonDown(const float x, const float y) override;

private:
	Crystal::Shader::ParticleDepthRenderer depthRenderer;
	Crystal::Shader::FrameBufferf depthBuffer;

	Crystal::Shader::NormalFilter normalFilter;
	Crystal::Shader::FrameBufferf normalBuffer;

	//Crystal::Shader::
	Crystal::Shader::PointRenderer pointRenderer;
	Crystal::Shader::FrameBufferf volumeBuffer;

	Crystal::Shader::BilateralFilter bilateralFilter;
	Crystal::Shader::FrameBufferf bluredBuffer;


	Crystal::Shader::AbsorptionRenderer absorptionRenderer;

	Crystal::Shader::DeferredRenderer deferredRenderer;
	int width;
	int height;

};

#endif