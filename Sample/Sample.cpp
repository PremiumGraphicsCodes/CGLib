#include "glfw.h"
#include "AntTweakBar.h"

#include <iostream>
#include <cstdlib>

#include "RenderingSample.h"
#include "FluidSample.h"
#include "RigidSample.h"
#include "CouplingSample.h"
#include "BulletSample.h"

#include "../Graphics/PerspectiveCamera.h"
#include "../Shader/LegacyRenderer.h"
#include "../Graphics/PointBuffer.h"

inline void TwEventMouseButtonGLFW3(GLFWwindow* window, int button, int action, int mods) { TwEventMouseButtonGLFW(button, action); }
inline void TwEventMousePosGLFW3(GLFWwindow* window, double xpos, double ypos) { TwMouseMotion(int(xpos), int(ypos)); }
inline void TwEventMouseWheelGLFW3(GLFWwindow* window, double xoffset, double yoffset) { TwEventMouseWheelGLFW(yoffset); }
inline void TwEventKeyGLFW3(GLFWwindow* window, int key, int scancode, int action, int mods) { TwEventKeyGLFW(key, action); }
inline void TwEventCharGLFW3(GLFWwindow* window, int codepoint) { TwEventCharGLFW(codepoint, GLFW_PRESS); }


void TW_CALL onFluid(void * /*clientData*/)
{
	FluidSample fluidSample;
	fluidSample.demonstrate();
}

void TW_CALL onRigid(void*)
{
	RigidSample rigidSample;
	rigidSample.demonstrate();
}

void TW_CALL onCoupling(void*)
{
	CouplingSample couplingSample;
	couplingSample.demonstrate();
}

void TW_CALL onBullet(void*)
{
	BulletSample bullet;
	bullet.demonstrate();
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
	TwAddButton(bar, "Fluid", onFluid, NULL, " label='Fluid' ");
	TwAddButton(bar, "Rigid", onRigid, nullptr, " label='Rigid' ");
	TwAddButton(bar, "Coupling", onCoupling, nullptr, " label='Coupling' ");
	TwAddButton(bar, "Bullet", onBullet, nullptr, " label = 'Bullet' ");

	auto window = glfwCreateWindow(512, 512, "Crystal Fluid Sample", nullptr, nullptr);
	if (!window) {
		std::cerr << "glufw CreateWindow failed." << std::endl;
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glEnable(GL_DEPTH_TEST);


	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW3);
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW3);
	glfwSetScrollCallback(window, (GLFWscrollfun)TwEventMouseWheelGLFW3);
	glfwSetKeyCallback(window, (GLFWkeyfun)TwEventKeyGLFW3);
	glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW3);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		TwDraw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	/*
	float speed = 0.0f;
	TwAddVarRW(bar, "speed", TW_TYPE_DOUBLE, &speed,
		" label='Rot speed' min=0 max=2 step=0.01 keyIncr=s keyDecr=S help='Rotation speed (turns/second)' ");
	TwAddButton(bar, "comment1", NULL, NULL, " label='ButtonTest' ");
	*/
	//RenderingSample renderingDemo;
	//renderingDemo.demonstrate();




	//RigidSample rigidSample;
	//rigidSample.demonstrate();

	//CouplingSample coupling;
	//coupling.demonstrate();

	TwTerminate();
	glfwTerminate();
	return EXIT_SUCCESS;
}