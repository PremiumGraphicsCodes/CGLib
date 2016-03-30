#ifndef __CRYSTAL_SAMPLE_POINT_RENDERER_SAMPLE_H__
#define __CRYSTAL_SAMPLE_POINT_RENDERER_SAMPLE_H__

#include "../Shader/GLee.h"
#include "../Shader/PointRenderer.h"

#include "ISample.h"
#include <memory>

class PointRendererSample : public ISample
{
public:
	PointRendererSample();

	void setup() override;

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

private:
	Crystal::Shader::ShaderObject shader;
	std::unique_ptr< Crystal::Shader::PointRenderer<float> > renderer;
};

#endif