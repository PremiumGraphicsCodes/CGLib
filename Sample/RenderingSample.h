#ifndef __CRYSTAL_SAMPLE_RENDERING_SAMPLE_H__
#define __CRYSTAL_SAMPLE_RENDERING_SAMPLE_H__

#include "glfw.h"
#include "ISample.h"
#include "../Shader/FrameBufferObject.h"
#include "../Shader/OnScreenRenderer.h"
#include "../Shader/DepthSmoothingRenderer.h"


class RenderingSample : public ISample
{
public:
	void setup() override;

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

private:
	Crystal::Shader::FrameBufferObject fbo;
	Crystal::Shader::Texture colorTexture;
	Crystal::Shader::DepthTexture depthTexture;
	Crystal::Shader::OnScreenRenderer onScreenRenderer;
	//Crystal::Shader::DepthTexture bluredDepthTexture;
};

#endif