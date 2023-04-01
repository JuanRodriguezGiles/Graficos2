#pragma once
#include "Engine/camera.h"

namespace engine
{
	class ENGINE_API firstPersonCamera : public camera
	{
	public:
		firstPersonCamera(renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector, PROJECTION projectionType);
		~firstPersonCamera();
		void rotateCamera(glm::vec2 mouseMovement);
		void setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector);
	};
}