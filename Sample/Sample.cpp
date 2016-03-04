#include "glfw.h"
#include "AntTweakBar.h"

#include <iostream>
#include <cstdlib>

#include "RenderingSample.h"
#include "FluidSample.h"
#include "RigidSample.h"
#include "CouplingSample.h"


void TW_CALL RunCB(void * /*clientData*/)
{
	;
}

int main(int argc, char* argv)
{
	if (!glfwInit()) {
		std::cerr << "glufw Init failed." << std::endl;
		exit(EXIT_FAILURE);
	}

	TwInit(TW_OPENGL, nullptr);
	TwBar* bar = TwNewBar("Bar");

	TwWindowSize(512, 512);
	TwAddButton(bar, "Run", RunCB, NULL, " label='Run Forest' ");

	float speed = 0.0f;
	TwAddVarRW(bar, "speed", TW_TYPE_DOUBLE, &speed,
		" label='Rot speed' min=0 max=2 step=0.01 keyIncr=s keyDecr=S help='Rotation speed (turns/second)' ");
	TwAddButton(bar, "comment1", NULL, NULL, " label='ButtonTest' ");

	RenderingSample renderingDemo;
	renderingDemo.demonstrate();



	//FluidSample fluidSample;
	//fluidSample.demonstrate();

	//RigidSample rigidSample;
	//rigidSample.demonstrate();

	//CouplingSample coupling;
	//coupling.demonstrate();


	glfwTerminate();
	return EXIT_SUCCESS;
}