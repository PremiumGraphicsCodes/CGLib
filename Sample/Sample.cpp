#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"

#include "glfw.h"
#include "AntTweakBar.h"

#include <iostream>
#include <cstdlib>

#include "RenderingSample.h"
#include "PointRendererSample.h"

#include "FluidSample.h"
#include "BulletRigidSample.h"
#include "BulletInteractionSample.h"
#include "IOSample.h"
#include "VolumeSample.h"
#include "ParticleSample.h"

#include "../Graphics/PerspectiveCamera.h"

namespace {
	Crystal::Graphics::PerspectiveCamera<float> camera;
	double prevPosX = 0.0f;
	double prevPosY = 0.0f;
	bool mousePressed = false;
	int pressedButton = 0;

	std::unique_ptr< ISample > activeSample;
}

void TwEventMouseButtonGLFW3(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
		mousePressed = true;
		pressedButton = button;
		glfwGetCursorPos(window, &prevPosX, &prevPosY);
	}
	else if (action == GLFW_RELEASE) {
		mousePressed = false;
	}

	TwEventMouseButtonGLFW(button, action);
}

void TwEventMousePosGLFW3(GLFWwindow* window, double xpos, double ypos)
{
	if (mousePressed) {
		const auto diffx = prevPosX - xpos;
		const auto diffy = prevPosY - ypos;
		prevPosX = xpos;
		prevPosY = ypos;
		if (pressedButton == GLFW_MOUSE_BUTTON_LEFT) {
			activeSample->onLeftDragging(diffx, diffy);
			camera.move(Crystal::Math::Vector3d<float>(diffx * -0.01, diffy * -0.01, 0.0f));
		}
		else if (pressedButton == GLFW_MOUSE_BUTTON_RIGHT) {
			camera.addAngle(Crystal::Math::Vector3d<float>(-diffx * 0.01, -diffy * 0.01, 0.0f));
		}
		else if (pressedButton == GLFW_MOUSE_BUTTON_MIDDLE) {
			camera.move(Crystal::Math::Vector3d<float>(0.0f, 0.0f, diffy*0.1));

		}

	}
	TwMouseMotion(int(xpos), int(ypos));
}
void TwEventMouseWheelGLFW3(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.move(Crystal::Math::Vector3d<float>(0.0f, 0.0f, yoffset*0.1));
	TwEventMouseWheelGLFW(yoffset);
}

void TwEventKeyGLFW3(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	TwEventKeyGLFW(key, action);
}

void TwEventCharGLFW3(GLFWwindow* window, int codepoint)
{
	TwEventCharGLFW(codepoint, GLFW_PRESS);
}


void TW_CALL onPointRender(void*)
{
	activeSample = std::make_unique<PointRendererSample>();
	activeSample->setup();
}

void TW_CALL onFluid(void * /*clientData*/)
{
	activeSample = std::make_unique<FluidSample>();
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

	camera.moveTo(Crystal::Math::Vector3d<float>(0.0, -5.0, -10.0));
	camera.setCameraXY();


	TwInit(TW_OPENGL, nullptr);
	TwBar* bar = TwNewBar("Bar");

	assert(glGetError() == GL_NO_ERROR);
	TwWindowSize(1024, 756);
	TwAddButton(bar, "Point", onPointRender, nullptr, " label='Point' ");

	TwAddButton(bar, "Fluid", onFluid, NULL, " label='Fluid' ");
	TwAddButton(bar, "Rigid", onBulletRigid, nullptr, " label = 'Rigid' ");
	TwAddButton(bar, "Coupling", onBulletInteraction, nullptr, " label = 'Coupling' ");
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