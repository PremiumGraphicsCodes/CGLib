#ifndef __CRYSTAL_SAMPLE_ID_RENDERER_SAMPLE_H__
#define __CRYSTAL_SAMPLE_ID_RENDERER_SAMPLE_H__

#include "../Shader/GLee.h"
#include "../Shader/IDRenderer.h"
#include "../Shader/FrameBuffer.h"

#include "ISample.h"
#include <memory>

class IDRendererSample : public ISample
{
public:
	IDRendererSample();

	void setup() override;

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

	void onMiddleButtonDown(float x, float y) override;

private:
	Crystal::Shader::IDRenderer renderer;
	Crystal::Shader::FrameBuffer frameBuffer;
	int width;
	int height;

};

#endif