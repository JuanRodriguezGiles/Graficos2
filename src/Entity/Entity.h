#pragma once
#include "Export.h"
namespace Engine
{
	class ENGINE_API IEntity
	{
	public:
		virtual void Draw() = 0;
	};
}