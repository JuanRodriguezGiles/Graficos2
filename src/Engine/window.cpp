#include "window.h"

#include "glew.h"
#include "glfw3.h"


namespace engine
{
	window::window(int width, int height, std::string windowName)
	{
		_height = height;
		_width = width;
		_window = glfwCreateWindow(width, height, &windowName[0], NULL, NULL);
	}
	window::~window()
	{

	}
	void window::init()
	{
		glfwMakeContextCurrent(_window);
	}
	GLFWwindow* window::getGLFWwindow()
	{
		return _window;
	}
	int window::getHeight()
	{
		return _height;
	}
	int window::getWidth()
	{
		return _width;
	}
}