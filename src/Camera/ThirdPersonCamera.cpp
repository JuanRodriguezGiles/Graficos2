#include "ThirdPersonCamera.h"

namespace Engine
{
	ThirdPersonCamera::ThirdPersonCamera(glm::vec3 Offset, glm::vec3 Position, glm::mat4 Perspective, glm::mat4 View) :Camera(Position, Perspective, View)
	{
		offset = Offset;
	}
	void ThirdPersonCamera::UpdatePosition(glm::vec3 Position) {
		view = glm::translate(view, Position);
	}
	void ThirdPersonCamera::UpdateRotation(glm::vec3 rotation, float angle) {
		view = glm::rotate(view, glm::radians(angle), rotation);
	}
	void ThirdPersonCamera::SetFront(glm::vec3 front) {
		cameraFront = front;
		view = glm::lookAt(position, front + position, up);
	}
	void ThirdPersonCamera::SetTarget(glm::vec3 targetPos)
	{
		this->targetPos = targetPos;
		position = targetPos + offset;
	}
}