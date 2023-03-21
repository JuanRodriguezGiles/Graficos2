#include "_window.h"
#include <iostream>
namespace Engine
{
	window::window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
	{
		createWindow(width, height, title, monitor, share);
	}
	void window::createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
	{
		_window = glfwCreateWindow(width, height, title, monitor, share);
	}
	void window::makeContextCurrent(GLFWwindow* window)
	{
		glfwMakeContextCurrent(window);
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			std::cout << "Error!" << std::endl;
	}
	int window::windowShouldClose(GLFWwindow* window)
	{
		return glfwWindowShouldClose(window);
	}
	GLFWwindow* window::get()
	{
		return _window;
	}
}