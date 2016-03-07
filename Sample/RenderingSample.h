#ifndef __CRYSTAL_SAMPLE_RENDERING_SAMPLE_H__
#define __CRYSTAL_SAMPLE_RENDERING_SAMPLE_H__

#include "glfw.h"
#include "ISample.h"


class RenderingSample : public ISample
{
public:
	RenderingSample() {}

	void setup() override;

	void demonstrate() override;

	void cleanup() override {};
};

#endif