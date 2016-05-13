#ifndef __CRYSTAL_SAMPLE_DEPTH_RENDERERING_SAMPLE_H__
#define __CRYSTAL_SAMPLE_DEPTH_RENDERERING_SAMPLE_H__

#include "../Shader/DepthRenderer.h"
#include "../Shader/OnScreenRenderer.h"
#include "../Shader/DepthBuffer.h"
#include "../Shader/LegacyRenderer.h"

#include "ISample.h"
#include <memory>

class DepthRenderingSample : public ISample
{
public:
	DepthRenderingSample() {};

	void setup() override;

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

private:
	Crystal::Shader::DepthBuffer depthBuffer;
	Crystal::Shader::DepthRenderer depthRenderer;
	Crystal::Shader::DepthTextureObject depthTexture2;
};

#endif