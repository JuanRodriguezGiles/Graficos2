#pragma once
#include "exports.h"
#include "entity.h"

namespace engine
{
	struct Light {
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
		virtual void setInitialValues() = 0;
		virtual void processIndividualValues() = 0;
		void draw();
	protected:
		unsigned int VAO;
		Light values;
	};
}