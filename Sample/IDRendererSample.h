#ifndef __CRYSTAL_SAMPLE_ID_RENDERER_SAMPLE_H__
#define __CRYSTAL_SAMPLE_ID_RENDERER_SAMPLE_H__

#include "../Shader/GLee.h"
#include "../Shader/IDRenderer.h"

#include "ISample.h"
#include <memory>

class IDRendererSample : public ISample
{
public:
	IDRendererSample();

	void setup() override;

	void demonstrate(const Crystal::Graphics::ICamera<float>& camera) override;

private:
	Crystal::Shader::IDRenderer renderer;
};

#endif