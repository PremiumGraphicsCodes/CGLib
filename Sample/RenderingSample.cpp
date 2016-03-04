#include "RenderingSample.h"

#include <iostream>

#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void RenderingSample::setup()
{
	window = glfwCreateWindow(512, 512, "Crystal Rendering Demo", nullptr, nullptr);
	if (!window) {
		std::cerr << "glufw CreateWindow failed." << std::endl;
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);


	glEnable(GL_DEPTH_TEST);

}

void RenderingSample::demonstrate()
{
	while (!glfwWindowShouldClose(window)) {
		PerspectiveCamera<float> camera;
		camera.setPos(Vector3d<float>(0.0, 0.0, -5.0));
		camera.setCameraXY();


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		int width;
		int height;

		LegacyRenderer renderer;
		LineBuffer buffer;
		Line3d<float> line(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0));
		ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);
		buffer.add(line, color);
		renderer.render(camera, buffer);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
