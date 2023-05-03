#include "firstPersonCamera.h"

namespace engine
{
	firstPersonCamera::firstPersonCamera(renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector, PROJECTION projectionType)
	{
		this->currentRenderer = currentRenderer;

		setProjetion(projectionType);

		setProjectionMatrix();
		setCameraTransform(position, lookPosition, upVector);
	}

	firstPersonCamera::~firstPersonCamera()
	{
	}

	void firstPersonCamera::rotateCamera(glm::vec2 mouseMovement)
	{
		glm::vec3 direction = getDirectionByMovement(mouseMovement);

		look = glm::normalize(direction);

		setCameraTransform(pos, look, up);
	}

	void firstPersonCamera::setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
	{
		pos = startingPosition;
		look = lookPosition;
		up = upVector;

		viewMatrix = glm::lookAt(startingPosition, pos + lookPosition, upVector);
		setViewMatrix();
		setCameraPosToRenderer();
	}
}
