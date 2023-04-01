#include "thirdPersonCamera.h"

namespace engine
{
	thirdPersonCamera::thirdPersonCamera(renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector, PROJECTION projectionType)
	{
		localPos = glm::vec3(0, 0, 0);
		targetPos = glm::vec3(0, 0, 0);
		distance = 50;

		this->currentRenderer = currentRenderer;
		//movementType = MOVEMENT_TYPE::THIRD_PERSON;

		setProjetion(projectionType);

		setProjectionMatrix();
		setCameraTransform(position, lookPosition, upVector);
	}
	thirdPersonCamera::~thirdPersonCamera()
	{
	}
	void thirdPersonCamera::updateTargetPos(glm::vec3 targetPosition)
	{
		targetPos = targetPosition;
	}
	void thirdPersonCamera::rotateCamera(glm::vec2 mouseMovement)
	{
		glm::vec3 direction = getDirectionByMovement(mouseMovement);
		direction.y = -direction.y;

		localPos = glm::normalize(direction) * distance;
		pos = targetPos + localPos;
		look = targetPos;

		setCameraTransform(pos, look, up);
	}
	void thirdPersonCamera::setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
	{
		pos = startingPosition;
		look = lookPosition;
		up = upVector;

		viewMatrix = glm::lookAt(startingPosition, lookPosition, upVector);

		setViewMatrix();
	}
}