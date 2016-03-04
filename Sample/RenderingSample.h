#ifndef __CRYSTAL_SAMPLE_RENDERING_SAMPLE_H__
#define __CRYSTAL_SAMPLE_RENDERING_SAMPLE_H__

#include "glfw.h"

class RenderingSample
{
public:
	RenderingSample() {
		setup();
	}

	void setup();

	void demonstrate();
private:
	GLFWwindow* window;
};

#endif