#include "glfw.h"

#include <iostream>
#include <cstdlib>

#include "../Math/Vector3d.h"
#include "../Math/Line3d.h"
#include "../Physics/PhysicsObject.h"
#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/VisualObject.h"
#include "../Shader/LegacyRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

int main(int argc, char* argv)
{
	if (!glfwInit()) {
		std::cerr << "glufw Init failed." << std::endl;
		exit(EXIT_FAILURE);
	}
	GLFWwindow* window = glfwCreateWindow( 512, 512, "Crystal Sample", nullptr, nullptr);
	if (!window) {
		std::cerr << "glufw CreateWindow failed." << std::endl;
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	PerspectiveCamera<float> camera;
	camera.setPos(Vector3d<float>(0.0, 0.0, -5.0));
	camera.setCameraXY();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		int width;
		int height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		//gluPerspective(30.0, width / height, 1.0, 100.0);

		LegacyRenderer renderer;
		LineBuffer buffer;
		Line3d<float> line(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0));
		ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);
		buffer.add(line, color);
		renderer.render(camera, buffer);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}