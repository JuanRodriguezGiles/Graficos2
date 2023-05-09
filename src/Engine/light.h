#pragma once
#include "exports.h"
#include "entity.h"

namespace engine
{
	struct Light {
		glm::vec3 position;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	struct textureData;
	class animation;
	class rederer;

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
		Light values;
	};
}