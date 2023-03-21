#include "Frame.h"

Frame::Frame(glm::vec2& _topRight, glm::vec2& _bottomRight, glm::vec2& _bottomLeft, glm::vec2& _topLeft)
{
	topRight = _topRight;
	bottomRight = _bottomRight;
	bottomLeft = _bottomLeft;
	topLeft = _topLeft;
}
