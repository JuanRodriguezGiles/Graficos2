#include "Camera.h"
namespace Engine
{
	Camera::Camera(glm::vec3 Position, glm::mat4 Perspective, glm::mat4 View)
	{
		perspective = Perspective;
		view = View;
		position = Position;
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		up = glm::vec3(0, 1, 0);
	}
}