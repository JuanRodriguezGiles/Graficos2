#include "directionalLight.h"
#include "renderer.h"

namespace engine
{
	void directionalLight::setInitialValues()
	{
		values.ambient = { 0.05f, 0.05f, 0.05f };
		values.diffuse = { 0.4f, 0.4f, 0.4f };
		values.specular = { 0.5f, 0.5f, 0.5f };

		direction = { -0.2f, -1.0f, -0.3f };
	}
	void directionalLight::processIndividualValues()
	{
		_renderer->processDirectionalLight(direction, values);
	}
}