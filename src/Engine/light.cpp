#include "light.h"
#include "renderer.h"

namespace engine
{
	light::light()
	{
		VAO = 0;
		_renderer = nullptr;
	}
	light::light(renderer* render)
	{
		VAO = 0;
		_renderer = render;

		model = glm::mat4(1.0f);
		translate = glm::mat4(1.0f);
		rotateX = glm::mat4(1.0f);
		rotateY = glm::mat4(1.0f);
		rotateZ = glm::mat4(1.0f);
		scale = glm::mat4(1.0f);

		v3pos = glm::vec3(0.0f);
		v3rot = glm::vec3(0.0f);
		v3scale = glm::vec3(1.0f);

		updateModelMatrix();

		setColor(glm::vec4(1.0f));
	}
	light::~light()
	{
	}
	void light::draw()
	{
		_renderer->shaderPro.use();
		_renderer->processLight(color);
	}
	void light::deinit()
	{


	}
}