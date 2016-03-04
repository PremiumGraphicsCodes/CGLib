#include "glfw.h"

#include <iostream>
#include <cstdlib>

#include "RenderingSample.h"
#include "FluidSample.h"
#include "RigidSample.h"
#include "CouplingSample.h"


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

	//RigidSample rigidSample;
	//rigidSample.demonstrate();

	//CouplingSample coupling;
	//coupling.demonstrate();

	glfwTerminate();
	return EXIT_SUCCESS;
}