#include "glfw.h"

#include <iostream>
#include <cstdlib>

#include "RenderingSample.h"
#include "FluidSample.h"




int main(int argc, char* argv)
{
	if (!glfwInit()) {
		std::cerr << "glufw Init failed." << std::endl;
		exit(EXIT_FAILURE);
	}

	//RenderingSample renderingDemo;
	//renderingDemo.demonstrate();

	FluidSample fluidSample;
	fluidSample.demonstrate();

	glfwTerminate();
	return EXIT_SUCCESS;
}