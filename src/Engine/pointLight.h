#pragma once
#include "light.h"

namespace engine
{
	class ENGINE_API pointLight : public light
	{
	public:
		pointLight();
		~pointLight();
		void setInitialValues() override;
		void processIndividualValues() override;
	private:
		static int lightsAmount;
		int index;
		float constant;
		float linear;
		float quadratic;
	};
}