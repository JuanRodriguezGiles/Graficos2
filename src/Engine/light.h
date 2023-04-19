#pragma once
#include "exports.h"
#include "entity.h"

namespace engine
{
	struct textureData;
	class animation;

	class ENGINE_API light : public entity
	{
	public:
		light();
		light(renderer* render);
		~light();
		void draw();
		void deinit();
	private:
		renderer* _render;
		unsigned int VAO;
		glm::vec3 color;
	};
}