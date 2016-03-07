#ifndef __CRYSTAL_SAMPLE_RENDERING_SAMPLE_H__
#define __CRYSTAL_SAMPLE_RENDERING_SAMPLE_H__

#include "glfw.h"
#include "ISample.h"


class RenderingSample : public ISample
{
public:
	void setup() override;

	void demonstrate() override;

private:
};

#endif