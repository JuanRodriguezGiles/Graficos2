#pragma once
#include "exports.h"

#include <string>
#include <iostream>

struct GLFWwindow;
//struct GLFWmonitor;

namespace engine
{
	class ENGINE_API window
	{
	public:
		window(int width, int height, std::string windowName);
		~window();
		void init();
		GLFWwindow* getGLFWwindow();
		int getWidth();
		int getHeight();

	private:
		GLFWwindow* _window;
		int _width;
		int _height;
	};
}