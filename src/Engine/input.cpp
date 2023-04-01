#include "input.h"
#include "glfw3.h"
#include "window.h"
#include <algorithm>

namespace engine
{
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	std::list<int> currentKeysDown;
	glm::vec2 mousePosition;
	glm::vec2 lastPos;
	glm::vec2 lastOffset;
	bool fistTimeCheckingMouse = true;

	const float sensitivity = 0.1f;

	input::input(window* window)
	{
		glfwSetKeyCallback(window->getGLFWwindow(), keyCallback);
		glfwSetCursorPosCallback(window->getGLFWwindow(), mouse_callback);
		lastPos.x = 400;
		lastPos.y = 300;
		fistTimeCheckingMouse = true;

		glfwSetInputMode(window->getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	input::~input()
	{

	}

	bool input::isKeyPressed(int keycode, window* window)
	{
		int aux = glfwGetKey(window->getGLFWwindow(), keycode);
		return aux == GLFW_PRESS;
	}

	bool input::isKeyDown(int keycode, window* window)
	{
		std::list<int>::iterator it = find(currentKeysDown.begin(), currentKeysDown.end(), keycode);
		if(it != currentKeysDown.end())
		{
			currentKeysDown.remove(keycode);
			return true;
		}
		return false;
	}
	glm::vec2 input::getMousePosition()
	{
		return mousePosition;
	}
	glm::vec2 input::getMouseOffSet()
	{
		return lastOffset;
	}
	void input::setOffset(glm::vec2 offSet)
	{
		lastOffset = offSet;
	}
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if(action == GLFW_PRESS)
		{
			currentKeysDown.push_front(key);
		}
		else if(action == GLFW_RELEASE)
		{
			currentKeysDown.remove(key);
		}
	}
	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (fistTimeCheckingMouse) // initially set to true
		{
			lastPos.x = xpos;
			lastPos.y = ypos;
			fistTimeCheckingMouse = false;
		}

		mousePosition = glm::vec2(xpos, ypos);

		lastOffset.x = xpos - lastPos.x;
		lastOffset.y = lastPos.y - ypos; // reversed since y-coordinates range from bottom to top
		lastPos.x = xpos;
		lastPos.y = ypos;

		lastOffset.x *= sensitivity;
		lastOffset.y *= sensitivity;
	}
}