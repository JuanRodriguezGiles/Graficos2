#pragma once
#include <vector>
#include "glm.hpp"
class Frame {
private:
public:
	glm::vec2 topRight;
	glm::vec2 bottomRight;
	glm::vec2 bottomLeft;
	glm::vec2 topLeft;
	Frame(glm::vec2& _topRight, glm::vec2& _bottomRight, glm::vec2& _bottomLeft, glm::vec2& _topLeft);
};