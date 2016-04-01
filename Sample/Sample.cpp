#if _WIN64
#include "windows.h"
#endif
#include "../Shader/ShaderObject.h"

#include "glfw.h"
#include "ISample.h"

#include <iostream>
#include <cstdlib>

#include "RenderingSample.h"
#include "PointRendererSample.h"

#include "FluidSample.h"
#include "RigidSample.h"
#include "BulletInteractionSample.h"
#include "IOSample.h"
#include "VolumeSample.h"
#include "ParticleSample.h"
#include "IDRendererSample.h"

#include "../Graphics/PerspectiveCamera.h"

namespace {
	Crystal::Graphics::PerspectiveCamera<float> camera;
	double prevPosX = 0.0f;
	double prevPosY = 0.0f;
	bool mousePressed = false;
	int pressedButton = 0;

	std::unique_ptr< ISample > activeSample;
}

void onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
		mousePressed = true;
		pressedButton = button;
		glfwGetCursorPos(window, &prevPosX, &prevPosY);
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			activeSample->onLeftButtonDown(prevPosX, prevPosY);
		}
		if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
			activeSample->onMiddleButtonDown(prevPosX, prevPosY);

		}

	}
	else if (action == GLFW_RELEASE) {
		mousePressed = false;
	}
}

void onMousePos(GLFWwindow* window, double xpos, double ypos)
{
	if (mousePressed) {
		const auto diffx = static_cast<float>( prevPosX - xpos );
		const auto diffy = static_cast<float>( prevPosY - ypos );
		prevPosX = xpos;
		prevPosY = ypos;
		if (pressedButton == GLFW_MOUSE_BUTTON_LEFT) {
			activeSample->onLeftDragging(diffx, diffy);
			camera.move(Crystal::Math::Vector3d<float>(diffx * -0.01f, diffy * -0.01f, 0.0f));
		}
		else if (pressedButton == GLFW_MOUSE_BUTTON_RIGHT) {
			camera.addAngle(Crystal::Math::Vector3d<float>(-diffx * 0.01f, -diffy * 0.01f, 0.0f));
		}
		else if (pressedButton == GLFW_MOUSE_BUTTON_MIDDLE) {
			//camera.move(Crystal::Math::Vector3d<float>(0.0f, 0.0f, diffy*0.1f));
			activeSample->onMiddleDragging(diffx, diffy);
		}

	}
}

void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.move(Crystal::Math::Vector3d<float>(0.0f, 0.0f, yoffset*0.1));
}

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch(key) {
		case GLFW_KEY_0 :
			activeSample = std::make_unique<PointRendererSample>();
			break;
		case GLFW_KEY_1 :
			activeSample = std::make_unique<FluidSample>();
			break;
		case GLFW_KEY_2 :
			activeSample = std::make_unique < RigidSample>();
			break;
		case GLFW_KEY_3 :
			activeSample = std::make_unique<BulletInteractionSample>();
			break;
	}
	activeSample->setup();

}

void onChar(GLFWwindow* window, unsigned int codepoint)
{
	activeSample->onKeyDown(codepoint);
}

//void TW_CALL onPointRender(void*)
//{
//}

//void TW_CALL onFluid(void * /*clientData*/)
//{
//}
//
//void TW_CALL onBulletRigid(void*)
//{
//	activeSample = std::make_unique<BulletRigidSample>();
//	activeSample->setup();
//}
//
//void TW_CALL onBulletInteraction(void*)
//{
//	activeSample = std::make_unique<BulletInteractionSample>();
//	activeSample->setup();
//}
//
//void TW_CALL onIO(void*)
//{
//	activeSample = std::make_unique<IOSample>();
//	activeSample->setup();
//}
//
//void TW_CALL onVolume(void*)
//{
//	activeSample = std::make_unique<VolumeSample>();
//	activeSample->setup();
//}
//
//void TW_CALL onParticle(void*)
//{
//	activeSample = std::make_unique<ParticleSample>();
//	activeSample->setup();
//}
//
//void TW_CALL onIDRendering(void*)
//{
//	activeSample = std::make_unique<IDRendererSample>();
//	activeSample->setup();
//
//}

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

	std::cout << "Press 1 : Fluid Simulation" << std::endl;
	std::cout << "Press 2 : Rigid Simulation" << std::endl;
	std::cout << "Press 3 : Coupling Simulation" << std::endl;

	std::cout << "Press 0 : Point Rendering" << std::endl;

	camera.moveTo(Crystal::Math::Vector3d<float>(0.0, -5.0, -10.0));
	camera.setCameraXY();


	//TwInit(TW_OPENGL, nullptr);
	//TwBar* bar = TwNewBar("Bar");

	assert(glGetError() == GL_NO_ERROR);
	int width = 1024;
	int height = 756;
	//TwAddButton(bar, "Point", onPointRender, nullptr, " label='Point' ");

	//TwAddButton(bar, "Fluid", onFluid, nullptr, " label='Fluid' ");
	//TwAddButton(bar, "Rigid", onBulletRigid, nullptr, " label = 'Rigid' ");
	//TwAddButton(bar, "Coupling", onBulletInteraction, nullptr, " label = 'Coupling' ");
	//TwAddButton(bar, "IO", onIO, nullptr, " label = 'IO' ");
	//TwAddButton(bar, "Volume", onVolume, nullptr, " label = 'Volume' ");
	//TwAddButton(bar, "Particle", onParticle, nullptr, " label = 'Particle' ");
	//TwAddButton(bar, "ID", onIDRendering, nullptr, " label = 'ID' ");

	glfwSetMouseButtonCallback(window, onMouseButton);
	glfwSetCursorPosCallback(window, onMousePos);
	glfwSetScrollCallback(window, onMouseWheel);
	glfwSetKeyCallback(window, onKey);
	glfwSetCharCallback(window, onChar);

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	activeSample = std::make_unique<RenderingSample>();

	while (!glfwWindowShouldClose(window)) {
		glfwGetWindowSize(window, &width, &height);
		activeSample->demonstrate(width, height, camera);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}