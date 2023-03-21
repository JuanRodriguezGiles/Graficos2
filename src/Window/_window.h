#pragma once
#include "Export.h"
#include "GL/glew.h"
#include "glfw3.h"
namespace Engine
{
	class ENGINE_API window
	{
		GLFWwindow* _window;
	public:
		window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
		void createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
		void makeContextCurrent(GLFWwindow* window);
		int windowShouldClose(GLFWwindow* window);
		GLFWwindow* get();
	};
}