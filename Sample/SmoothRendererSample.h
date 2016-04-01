#ifndef __CRYSTAL_SAMPLE_SMOOTH_RENDERER_SAMPLE_H__
#define __CRYSTAL_SAMPLE_SMOOTH_RENDERER_SAMPLE_H__

#include "../Shader/GLee.h"
#include "../Shader/SmoothRenderer.h"

#include "ISample.h"
#include <memory>

class SmoothRendererSample : public ISample
{
public:
	SmoothRendererSample();

	void setup() override;

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

private:
	Crystal::Shader::SmoothRenderer renderer;
};

#endif