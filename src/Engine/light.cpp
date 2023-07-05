#include "light.h"
#include "renderer.h"
//#include "glew.h"
//#include "glfw3.h"
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

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

		worldModel = glm::mat4(1.0f);
		localTranslate = glm::mat4(1.0f);
		localRotateX = glm::mat4(1.0f);
		localRotateY = glm::mat4(1.0f);
		localRotateZ = glm::mat4(1.0f);
		localScale = glm::mat4(1.0f);

		v3localPos = glm::vec3(0.0f);
		v3localRot = glm::vec3(0.0f);
		v3localScale = glm::vec3(1.0f);

		updateModelMatrix();

		setColor(glm::vec4(1.0f));

		values.ambient = glm::vec3(0.2f);
		values.diffuse = glm::vec3(0.5f);
		values.specular = glm::vec3(1);

	}
	light::~light()
	{
	}
	void light::draw()
	{
		_renderer->shader.use();
		_renderer->processLight(color, v3localPos);

		processIndividualValues();
	}
}