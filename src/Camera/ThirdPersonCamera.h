#pragma once
#include "Export.h"
#include "Camera.h"

namespace Engine
{
	class ENGINE_API ThirdPersonCamera : public Camera
	{
	private:
		glm::vec3 offset;
		glm::vec3 targetPos;
	public:
		ThirdPersonCamera(glm::vec3 Offset, glm::vec3 Position, glm::mat4 Perspective, glm::mat4 View);
		void UpdatePosition(glm::vec3 Position) override;
		void UpdateRotation(glm::vec3 rotation, float angle) override;
		void SetFront(glm::vec3 front) override;
		void SetTarget(glm::vec3 targetPos);
	};
}