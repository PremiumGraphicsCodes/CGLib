#ifndef __CRYSTAL_SAMPLE_GEOMETRY_RENDERERING_SAMPLE_H__
#define __CRYSTAL_SAMPLE_GEOMETRY_RENDERERING_SAMPLE_H__

#include "../Shader/GLee.h"
#include "../Shader/GeometryRenderer.h"
#include "../Shader/OnScreenRenderer.h"
#include "../Shader/SSNormalRenderer.h"
#include "../Shader/DeferredRenderer.h"

#include "ISample.h"
#include <memory>

class GeometryRenderingSample : public ISample
{
public:
	GeometryRenderingSample(){};

	void setup() override;

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

private:
	Crystal::Shader::GeometryRenderer renderer;
	Crystal::Shader::SSNormalRenderer normalRenderer;
	Crystal::Shader::DepthTexture depthTexture;
	Crystal::Shader::DepthBuffer depthBuffer;
	Crystal::Shader::FrameBuffer normalBuffer;
	Crystal::Shader::OnScreenRenderer onScreenRenderer;
	Crystal::Shader::DeferredRenderer deferredRenderer;
};

#endif