#pragma once
#include "Engine/camera.h"

namespace engine
{
	class ENGINE_API thirdPersonCamera : public camera
	{
	public:
		thirdPersonCamera(renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector, PROJECTION projectionType);
		~thirdPersonCamera();
		void updateTargetPos(glm::vec3 targetPosition);
		void rotateCamera(glm::vec2 mouseMovement);
		void setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector);
	private:
		glm::vec3 targetPos;
		glm::vec3 localPos;
		float distance; //distance from target

	};
}