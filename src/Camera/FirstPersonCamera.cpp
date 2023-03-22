#include "FirstPersonCamera.h"

namespace Engine
{
	void FirstPersonCamera::UpdatePosition(glm::vec3 Position){
		view = glm::translate(view, Position);
	}
	void FirstPersonCamera::UpdateRotation(glm::vec3 rotation, float angle) {
		view = glm::rotate(view, glm::radians(angle), rotation);
	}
	void FirstPersonCamera::SetFront(glm::vec3 front) {
		cameraFront = front;
		view = glm::lookAt(position, front + position, up);
	}
}