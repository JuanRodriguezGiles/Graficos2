#include "light.h"
#include "glew.h"
#include "glfw3.h"

namespace engine
{
	light::light()
	{
		VAO = 0;
	}
	light::light(renderer* render)
	{
		VAO = 0;
		_renderer = render;
	}
	light::~light()
	{
	}
	void light::draw()
	{
	}
	void light::deinit()
	{

	}
}
