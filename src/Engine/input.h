#pragma once
#include "exports.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <list>

namespace engine
{
	class window;

	class ENGINE_API input
	{
	public:
		input(window* window);
		~input();
		bool isKeyPressed(int keycode, window* window);
		bool isKeyDown(int keycode, window* window);
		glm::vec2 getMousePosition();
		glm::vec2 getMouseOffSet();
		void setOffset(glm::vec2 offSet);
	private:
	};
}
