#pragma once
#include "light.h"

namespace engine
{
	class ENGINE_API spotLight : public light
	{
	public:
		spotLight();
		spotLight(renderer* render);
		~spotLight();
		void setInitialValues() override;
		void processIndividualValues() override;
		void setDirection(glm::vec3 direction, bool normalized);
	private:
		glm::vec3 direction;
		float cutOff;
		float outerCutOff;
		float constant;
		float linear;
		float quadratic;
	};
}