#include "glfw.h"
#include "AntTweakBar.h"

#include <iostream>
#include <cstdlib>

#include "RenderingSample.h"
#include "FluidSample.h"
#include "BulletSample.h"
#include "BulletRigidSample.h"
#include "BulletInteractionSample.h"
#include "IOSample.h"
#include "VolumeSample.h"
#include "ParticleSample.h"

#include "../Graphics/PerspectiveCamera.h"

namespace {
	Crystal::Graphics::PerspectiveCamera<float> camera;
	bool mousePressed = false;
}

void TwEventMouseButtonGLFW3(GLFWwindow* window, int button, int action, int mods)
{
	if (action == TW_MOUSE_PRESSED) {
		mousePressed = true;
	}
	else if (action == TW_MOUSE_RELEASED) {
		mousePressed = false;
	}

	TwEventMouseButtonGLFW(button, action);
}
void TwEventMousePosGLFW3(GLFWwindow* window, double xpos, double ypos)
{
	TwMouseMotion(int(xpos), int(ypos));
}
void TwEventMouseWheelGLFW3(GLFWwindow* window, double xoffset, double yoffset)
{
	TwEventMouseWheelGLFW(yoffset);
}
inline void TwEventKeyGLFW3(GLFWwindow* window, int key, int scancode, int action, int mods) { TwEventKeyGLFW(key, action); }
inline void TwEventCharGLFW3(GLFWwindow* window, int codepoint) { TwEventCharGLFW(codepoint, GLFW_PRESS); }

std::unique_ptr< ISample > activeSample;


void TW_CALL onFluid(void * /*clientData*/)
{
	activeSample = std::make_unique<FluidSample>();
	activeSample->setup();
}

void TW_CALL onBullet(void*)
{
	activeSample = std::make_unique<BulletSample>();
	activeSample->setup();
}

void TW_CALL onBulletRigid(void*)
{
	activeSample = std::make_unique<BulletRigidSample>();
	activeSample->setup();
}

void TW_CALL onBulletInteraction(void*)
{
	activeSample = std::make_unique<BulletInteractionSample>();
	activeSample->setup();
}

void TW_CALL onIO(void*)
{
	activeSample = std::make_unique<IOSample>();
	activeSample->setup();
}

void TW_CALL onVolume(void*)
{
	activeSample = std::make_unique<VolumeSample>();
	activeSample->setup();
}

void TW_CALL onParticle(void*)
{
	activeSample = std::make_unique<ParticleSample>();
	activeSample->setup();
}

int main(int argc, char* argv)
{
	if (!glfwInit()) {
		std::cerr << "glufw Init failed." << std::endl;
		exit(EXIT_FAILURE);
	}

	auto window = glfwCreateWindow(1024, 756, "Crystal Sample", nullptr, nullptr);
	if (!window) {
		//std::cerr << "glufw CreateWindow failed." << std::endl;
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	camera.moveTo(Crystal::Math::Vector3d<float>(-20.0, -5.0, -10.0));
	camera.setCameraXY();


	TwInit(TW_OPENGL, nullptr);
	TwBar* bar = TwNewBar("Bar");

	TwWindowSize(1024, 756);
	TwAddButton(bar, "Fluid", onFluid, NULL, " label='Fluid' ");
	TwAddButton(bar, "Bullet", onBullet, nullptr, " label = 'Bullet' ");
	TwAddButton(bar, "BulletRigid", onBulletRigid, nullptr, " label = 'BulletRigid' ");
	TwAddButton(bar, "BulletInteraction", onBulletInteraction, nullptr, " label = 'BulletInteraction' ");
	TwAddButton(bar, "IO", onIO, nullptr, " label = 'IO' ");
	TwAddButton(bar, "Volume", onVolume, nullptr, " label = 'Volume' ");
	TwAddButton(bar, "Particle", onParticle, nullptr, " label = 'Particle' ");


	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW3);
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW3);
	glfwSetScrollCallback(window, (GLFWscrollfun)TwEventMouseWheelGLFW3);
	glfwSetKeyCallback(window, (GLFWkeyfun)TwEventKeyGLFW3);
	glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW3);

	activeSample = std::make_unique<RenderingSample>();

	while (!glfwWindowShouldClose(window)) {
		activeSample->demonstrate(camera);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		TwDraw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	TwTerminate();
	glfwTerminate();
	return EXIT_SUCCESS;
}