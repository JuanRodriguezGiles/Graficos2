#pragma once
#include "exports.h"
#include "entity.h"

namespace engine
{
	struct textureData;
	class animation;
	class renderer;

	class ENGINE_API light : public entity
	{
	public:
		light();
		light(renderer* render);
		~light();
		void draw();
		void deinit();
	private:
		unsigned int VAO;
	};
}