#include <iostream>
#include <cstdlib>

#include "gtest/gtest.h"

#include "glfw.h"

#include <gl/gl.h>

//using namespace Crystal::Shader;

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	const auto width = 32;
	const auto height = 32;
	if (!glfwInit()) {
		std::cerr << "glfwInit failed." << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	auto window = glfwCreateWindow(width, height, "ShaderTest", nullptr, nullptr);
	if (!window) {
		std::cerr << "glfwCreateWindow failed." << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	/*
	if (!glfwInit()) {
		std::cerr << "glfwInit failed." << std::endl;
		exit(EXIT_FAILURE);
	}
	*/

	//glClearColor(0, 0, 1, 1);

	return RUN_ALL_TESTS();
}
