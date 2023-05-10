#include "pointLight.h"
#include "renderer.h"

namespace engine
{
	pointLight::pointLight()
	{
		index = lightsAmount;

		if (lightsAmount == 4)
		{
			lightsAmount = 0;
		}
		else
		{
			lightsAmount++;
		}
	}
	pointLight::~pointLight()
	{
	}
	void pointLight::setInitialValues()
	{
		values.ambient = { 0.05f, 0.05f, 0.05f };
		values.diffuse = { 0.4f, 0.4f, 0.4f };
		values.specular = { 0.5f, 0.5f, 0.5f };

		constant = 1.0f;
		linear = 0.09f;
		quadratic = 0.032f;
	}
	void pointLight::processIndividualValues()
	{
		_renderer->processPointLight(constant, linear, quadratic, values, index);
	}
}