#pragma once
#include "Export.h"
#include "Camera.h"

namespace Engine
{
	class ENGINE_API FirstPersonCamera :public Camera
	{
	private:
	public:
		FirstPersonCamera(glm::vec3 Position, glm::mat4 Perspective, glm::mat4 View) :Camera(Position, Perspective, View) {};
		void UpdatePosition(glm::vec3 Position) override;
		void UpdateRotation(glm::vec3 rotation, float angle) override;
		void SetFront(glm::vec3 front) override;
	};
}