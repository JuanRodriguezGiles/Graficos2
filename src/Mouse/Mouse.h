#pragma once
#include "Export.h"
namespace Engine
{
	class ENGINE_API Mouse
	{
	public:
		bool firstMouse;
		float lastX;
		float lastY;
		float yaw;
		float pitch;
		Mouse(float x, float y)
		{
			firstMouse = true;
			lastX = x;
			lastY = y;
			yaw = 0;
			pitch = 0;
		}
	private:
	};
}