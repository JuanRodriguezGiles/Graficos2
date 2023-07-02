#pragma once
#include "light.h";

namespace engine
{
	class ENGINE_API pointLight : public light
	{
	public:
		pointLight();
		pointLight(renderer* render);
		~pointLight();
		void setInitialValues() override;
		void processIndividualValues() override;
	private:
		float constant;
		float linear;
		float quadratic;
	};
}