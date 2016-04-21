#ifndef __CRYSTAL_SAMPLE_GEOMETRY_RENDERERING_SAMPLE_H__
#define __CRYSTAL_SAMPLE_GEOMETRY_RENDERERING_SAMPLE_H__

#include "../Shader/GLee.h"
#include "../Shader/GeometryRenderer.h"

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
};

#endif