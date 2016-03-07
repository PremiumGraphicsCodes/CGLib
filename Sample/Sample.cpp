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

std::unique_ptr< ISample > activeSample;

void TW_CALL onFluid(void * /*clientData*/)
{
	activeSample->cleanup();
	activeSample = std::make_unique<FluidSample>();
	activeSample->setup();
}

void TW_CALL onRigid(void*)
{
	activeSample->cleanup();
	activeSample = std::make_unique<RigidSample>();
	activeSample->setup();
}

void TW_CALL onCoupling(void*)
{
	activeSample->cleanup();
	activeSample = std::make_unique<CouplingSample>();
	activeSample->setup();
}

void TW_CALL onBullet(void*)
{
	activeSample->cleanup();
	activeSample = std::make_unique<BulletSample>();
	activeSample->setup();
}

int main(int argc, char* argv)
{
	if (!glfwInit()) {
		std::cerr << "glufw Init failed." << std::endl;
		exit(EXIT_FAILURE);
	}

	auto window = glfwCreateWindow(512, 512, "Crystal Sample", nullptr, nullptr);
	if (!window) {
		//std::cerr << "glufw CreateWindow failed." << std::endl;
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);


	TwInit(TW_OPENGL, nullptr);
	TwBar* bar = TwNewBar("Bar");

	TwWindowSize(512, 512);
	TwAddButton(bar, "Fluid", onFluid, NULL, " label='Fluid' ");
	TwAddButton(bar, "Rigid", onRigid, nullptr, " label='Rigid' ");
	TwAddButton(bar, "Coupling", onCoupling, nullptr, " label='Coupling' ");
	TwAddButton(bar, "Bullet", onBullet, nullptr, " label = 'Bullet' ");

	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW3);
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW3);
	glfwSetScrollCallback(window, (GLFWscrollfun)TwEventMouseWheelGLFW3);
	glfwSetKeyCallback(window, (GLFWkeyfun)TwEventKeyGLFW3);
	glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW3);

	activeSample = std::make_unique<RenderingSample>();
	activeSample->setup();

	while (!glfwWindowShouldClose(window)) {
		activeSample->demonstrate();
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		TwDraw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	activeSample->cleanup();

	TwTerminate();
	glfwTerminate();
	return EXIT_SUCCESS;
}