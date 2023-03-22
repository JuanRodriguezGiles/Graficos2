#pragma once
#include "Export.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace Engine
{
	class ENGINE_API Camera
	{
	private:

	public:
		Camera(glm::vec3 Position, glm::mat4 Perspective, glm::mat4 View);
		glm::mat4 perspective;
		glm::mat4 view;
		glm::vec3 cameraFront;
		glm::vec3 up;
		glm::vec3 position = glm::vec3(0, 0, 0);
		glm::vec4 rotation = glm::vec4(1, 0, 0, 0);
		virtual void UpdatePosition(glm::vec3 Position) = 0;
		virtual void UpdateRotation(glm::vec3 rotation, float angle) = 0;
		virtual void SetFront(glm::vec3 front) = 0;
		glm::vec3 GetFront() {
			return cameraFront;
		}
		glm::vec3 GetPosition() {
			return position;
		}
		glm::vec3 GetUp() {
			return up;
		}
	};
}