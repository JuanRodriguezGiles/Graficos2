#include "renderer.h"
#include <string>
#include "glew.h"
#include "glfw3.h"

namespace engine
{
	renderer::renderer()
	{
		currentWindow = NULL;
		viewMatrix = glm::mat4();
		projectionMatrix = glm::mat4();
		clearColor = glm::vec4(0, 0, 0, 1);
	}
	renderer::renderer(window* window)
	{
		clearColor = glm::vec4(0, 0, 0, 1);

		currentWindow = window;

		viewMatrix = glm::mat4(1.0f);
		projectionMatrix = glm::mat4(1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	renderer::~renderer()
	{

	}
	void renderer::setCurrentWindow(window* window)
	{
		currentWindow = window;
	}
	void renderer::startDraw()
	{
		//Sets the color that will be used to clear the color buffer of the current OpenGL context
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		//Clear the buffers of the current rendering context
		//Depth buffer/z-buffer: determine which pixels of a scene should be visible and which should be hidden by other objects in the scene
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void renderer::endDraw()
	{
		//Double buffer, swap front and back buffers from the window (back buffer hold next frame)
		glfwSwapBuffers(currentWindow->getGLFWwindow());
	}
	
	void renderer::setShaderInfo(glm::vec4 color, unsigned int textures[], MATERIAL material)
	{
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		unsigned int colorLoc = glGetUniformLocation(shaderPro.ID, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(shaderPro.ID, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));

		Material materialValue = GetMaterialData(material);

		int diffuse = 0;
		int specular = 1;

		unsigned int textureLoc = glGetUniformLocation(shaderPro.ID, "ourTexture");
		glUniform1f(textureLoc, (GLfloat)textures[0]);

		unsigned int materialLoc = glGetUniformLocation(shaderPro.ID, "material.diffuse");
		glUniform1i(materialLoc, diffuse);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		materialLoc = glGetUniformLocation(shaderPro.ID, "material.specular");
		glUniform1i(materialLoc, specular);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);

		materialLoc = glGetUniformLocation(shaderPro.ID, "material.shininess");
		glUniform1fv(materialLoc, 1, &(materialValue.shininess));
	}
	void renderer::drawRequest(glm::mat4 modelMatrix, unsigned int VAO, unsigned int vertices)
	{
		//Uniform: special variables in shaders that can be set from the application and are constant across all vertices or fragments processed by the shader
		unsigned int modelLoc = glGetUniformLocation(shaderPro.ID, "model");
		//set the value of a 4x4 matrix uniform variable in a shader program.
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		unsigned int viewLoc = glGetUniformLocation(shaderPro.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		unsigned int projectionLoc = glGetUniformLocation(shaderPro.ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		//vertex array is a collection of vertex attribute data that describes the properties of vertices in a mesh or object (pos color tex)
		//VAO container object that stores the state of a vertex array, including the bindings of vertex buffer objects (VBOs) that contain vertex attribute data
		//Bind == reuse the same vertex array across multiple draw calls without having to re-specify the same state every time
		glBindVertexArray(VAO);


		//render geometric primitives by specifying a list of indices that reference vertex data stored in VBO
		glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
	}
	void renderer::processLight(glm::vec3 lightColor, glm::vec3 lightPos)
	{
		unsigned int lightColorLoc = glGetUniformLocation(shaderPro.ID, "lightColor");
		glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

		unsigned int ambientStengthLoc = glGetUniformLocation(shaderPro.ID, "ambientStrength");
		glUniform1fv(ambientStengthLoc, 1, &(ambientLight));

		unsigned int lightPosLoc = glGetUniformLocation(shaderPro.ID, "lightPos");
		glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
	}
	void renderer::processDirectionalLight(glm::vec3 direction, Light light)
	{
		unsigned int lightDirLoc = glGetUniformLocation(shaderPro.ID, "dirLight.direction");
		glUniform3fv(lightDirLoc, 1, glm::value_ptr(direction));

		unsigned int lightAmbientLoc = glGetUniformLocation(shaderPro.ID, "dirLight.ambient");
		glUniform3fv(lightAmbientLoc, 1, glm::value_ptr(light.ambient));

		unsigned int lighDiffusetLoc = glGetUniformLocation(shaderPro.ID, "dirLight.diffuse");
		glUniform3fv(lighDiffusetLoc, 1, glm::value_ptr(light.diffuse));

		unsigned int lightSpecularLoc = glGetUniformLocation(shaderPro.ID, "dirLight.specular");
		glUniform3fv(lightSpecularLoc, 1, glm::value_ptr(light.specular));

		unsigned int lightColorLoc = glGetUniformLocation(shaderPro.ID, "dirLight.color");
		glUniform3fv(lightColorLoc, 1, glm::value_ptr(light.color));
	}
	void renderer::processPointLight(float constant, float linear, float quadratic, glm::vec3 position, Light light, int index)
	{
		unsigned int lightAmbientLoc;
		unsigned int lighDiffusetLoc;
		unsigned int lightSpecularLoc;
		unsigned int lightConstantLoc;
		unsigned int lightLinearLoc;
		unsigned int lightQuadraticLoc;
		unsigned int lightPosLoc;
		unsigned int lightColorLoc;

		switch (index)
		{
		case 0:
			lightAmbientLoc = glGetUniformLocation(shaderPro.ID, "pointLights[0].ambient");
			lighDiffusetLoc = glGetUniformLocation(shaderPro.ID, "pointLights[0].diffuse");
			lightSpecularLoc = glGetUniformLocation(shaderPro.ID, "pointLights[0].specular");
			lightConstantLoc = glGetUniformLocation(shaderPro.ID, "pointLights[0].constant");
			lightLinearLoc = glGetUniformLocation(shaderPro.ID, "pointLights[0].linear");
			lightQuadraticLoc = glGetUniformLocation(shaderPro.ID, "pointLights[0].quadratic");
			lightPosLoc = glGetUniformLocation(shaderPro.ID, "pointLights[0].position");
			lightColorLoc = glGetUniformLocation(shaderPro.ID, "pointLights[0].color");
			break;
		case 1:
			lightAmbientLoc = glGetUniformLocation(shaderPro.ID, "pointLights[1].ambient");
			lighDiffusetLoc = glGetUniformLocation(shaderPro.ID, "pointLights[1].diffuse");
			lightSpecularLoc = glGetUniformLocation(shaderPro.ID, "pointLights[1].specular");
			lightConstantLoc = glGetUniformLocation(shaderPro.ID, "pointLights[1].constant");
			lightLinearLoc = glGetUniformLocation(shaderPro.ID, "pointLights[1].linear");
			lightQuadraticLoc = glGetUniformLocation(shaderPro.ID, "pointLights[1].quadratic");
			lightPosLoc = glGetUniformLocation(shaderPro.ID, "pointLights[1].position");
			lightColorLoc = glGetUniformLocation(shaderPro.ID, "pointLights[1].color");
			break;
		case 2:
			lightAmbientLoc = glGetUniformLocation(shaderPro.ID, "pointLights[2].ambient");
			lighDiffusetLoc = glGetUniformLocation(shaderPro.ID, "pointLights[2].diffuse");
			lightSpecularLoc = glGetUniformLocation(shaderPro.ID, "pointLights[2].specular");
			lightConstantLoc = glGetUniformLocation(shaderPro.ID, "pointLights[2].constant");
			lightLinearLoc = glGetUniformLocation(shaderPro.ID, "pointLights[2].linear");
			lightQuadraticLoc = glGetUniformLocation(shaderPro.ID, "pointLights[2].quadratic");
			lightPosLoc = glGetUniformLocation(shaderPro.ID, "pointLights[2].position");
			lightColorLoc = glGetUniformLocation(shaderPro.ID, "pointLights[2].color");
			break;
		case 3:
			lightAmbientLoc = glGetUniformLocation(shaderPro.ID, "pointLights[3].ambient");
			lighDiffusetLoc = glGetUniformLocation(shaderPro.ID, "pointLights[3].diffuse");
			lightSpecularLoc = glGetUniformLocation(shaderPro.ID, "pointLights[3].specular");
			lightConstantLoc = glGetUniformLocation(shaderPro.ID, "pointLights[3].constant");
			lightLinearLoc = glGetUniformLocation(shaderPro.ID, "pointLights[3].linear");
			lightQuadraticLoc = glGetUniformLocation(shaderPro.ID, "pointLights[3].quadratic");
			lightPosLoc = glGetUniformLocation(shaderPro.ID, "pointLights[3].position");
			lightColorLoc = glGetUniformLocation(shaderPro.ID, "pointLights[3].color");
			break;
		}

		//pointLights
		glUniform3fv(lightAmbientLoc, 1, glm::value_ptr(light.ambient));
		glUniform3fv(lighDiffusetLoc, 1, glm::value_ptr(light.diffuse));
		glUniform3fv(lightSpecularLoc, 1, glm::value_ptr(light.specular));
		glUniform3fv(lightColorLoc, 1, glm::value_ptr(light.color));
		glUniform3fv(lightPosLoc, 1, glm::value_ptr(position));
		glUniform1fv(lightConstantLoc, 1, &constant);
		glUniform1fv(lightLinearLoc, 1, &linear);
		glUniform1fv(lightQuadraticLoc, 1, &quadratic);
	}
	void renderer::processSpotLight(glm::vec3 direction, float constant, float linear, float quadratic, glm::vec3 position, Light light, float cutOff, float outerCutOff)
	{
		unsigned int lightDirLoc = glGetUniformLocation(shaderPro.ID, "spotLight.direction");
		glUniform3fv(lightDirLoc, 1, glm::value_ptr(direction));

		unsigned int lightPosLoc = glGetUniformLocation(shaderPro.ID, "spotLight.position");
		glUniform3fv(lightPosLoc, 1, glm::value_ptr(position));

		unsigned int lightCutOffLoc = glGetUniformLocation(shaderPro.ID, "spotLight.cutOff");
		glUniform1fv(lightCutOffLoc, 1, &cutOff);

		unsigned int lightOuterCutOffLoc = glGetUniformLocation(shaderPro.ID, "spotLight.outerCutOff");
		glUniform1fv(lightOuterCutOffLoc, 1, &outerCutOff);

		unsigned int lightConstantLoc = glGetUniformLocation(shaderPro.ID, "spotLight.constant");
		glUniform1fv(lightConstantLoc, 1, &constant);

		unsigned int lightLinearLoc = glGetUniformLocation(shaderPro.ID, "spotLight.linear");
		glUniform1fv(lightLinearLoc, 1, &linear);

		unsigned int lightQuadraticLoc = glGetUniformLocation(shaderPro.ID, "spotLight.quadratic");
		glUniform1fv(lightQuadraticLoc, 1, &quadratic);

		unsigned int lightAmbientLoc = glGetUniformLocation(shaderPro.ID, "spotLight.ambient");
		glUniform3fv(lightAmbientLoc, 1, glm::value_ptr(light.ambient));

		unsigned int lighDiffusetLoc = glGetUniformLocation(shaderPro.ID, "spotLight.diffuse");
		glUniform3fv(lighDiffusetLoc, 1, glm::value_ptr(light.diffuse));

		unsigned int lightSpecularLoc = glGetUniformLocation(shaderPro.ID, "spotLight.specular");
		glUniform3fv(lightSpecularLoc, 1, glm::value_ptr(light.specular));

		unsigned int lightColorLoc = glGetUniformLocation(shaderPro.ID, "spotLight.color");
		glUniform3fv(lightColorLoc, 1, glm::value_ptr(light.color));
	}
	void renderer::createBaseBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		//Create 1 vertex array object
		glGenVertexArrays(1, &VAO);
		//Create buffer object (store data in memory on the GPU)

		//VBO store vertex data for rendering
		glGenBuffers(1, &VBO);
		//Element buffer object, stores indices of VBO
		glGenBuffers(1, &EBO);
	}
	void renderer::createExtraBuffer(unsigned int& buffer, int size)
	{
		glGenBuffers(size, &buffer);
	}
	void renderer::bindBaseBufferRequest(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices, unsigned int sizeOfVertices, unsigned int* indices, unsigned int sizeOfIndices)
	{
		//Binds VAO and two buffer objects (a Vertex Buffer Object (VBO) and an Element Buffer Object (EBO))
		//to the OpenGL context, and fills the VBO and EBO with vertex data and index data, respectively.

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);
	}
	void renderer::bindExtraBuffer(unsigned int buffer, float* data, unsigned int sizeOfData, unsigned int bufferType)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, bufferType);
	}
	void renderer::deleteBaseBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	void renderer::deleteExtraBuffer(unsigned int& buffer, int size)
	{
		glDeleteBuffers(size, &buffer);
	}
	void renderer::setClearColor(glm::vec4 color)
	{
		clearColor = color;
	}
	void renderer::setViewMatrix(glm::mat4 viewMatrix)
	{
		this->viewMatrix = viewMatrix;
	}
	void renderer::setViewPosition(glm::vec3 viewPos)
	{
		unsigned int viewPosLoc = glGetUniformLocation(shaderPro.ID, "viewPos");
		glUniform3fv(viewPosLoc, 1, glm::value_ptr(viewPos));
	}
	void renderer::setProjectionMatrix(glm::mat4 projectionMatrix)
	{
		this->projectionMatrix = projectionMatrix;
	}
	window* renderer::getCurrentWindow()
	{
		return currentWindow;
	}
	Material renderer::GetMaterialData(MATERIAL material)
	{
		Material mat;

		switch (material)
		{
		case MATERIAL::EMERALD:
			mat = Material(glm::vec3(0.0215f, 0.0215f, 0.0215f), 0, 0, 0.6f * 100);
			break;
		case MATERIAL::PEARL:
			mat = Material(glm::vec3(0.25f, 0.20725f, 0.20725f), 0, 0, 0.088f * 100);
			break;
		case MATERIAL::BRONZE:
			mat = Material(glm::vec3(0.2125f, 0.1275f, 0.054f), 0, 0, 0.2f * 100);
			break;
		case MATERIAL::GOLD:
			mat = Material(glm::vec3(0.24725f, 0.1995f, 0.0745f), 0, 0, 0.4f * 100);
			break;
		case MATERIAL::CYAN_PLASTIC:
			mat = Material(glm::vec3(0.0f, 0.1f, 0.06f), 0, 0, .25f * 10);
			break;
		case MATERIAL::RED_PLASTIC:
			mat = Material(glm::vec3(0.0f, 0.0f, 0.0f), 0, 0, .25f * 10);
			break;
		case MATERIAL::GREEN_RUBBER:
			mat = Material(glm::vec3(0.0f, 0.5f, 0.0f), 0, 0, .078125f * 50);
			break;
		case MATERIAL::YELLOW_RUBBER:
			mat = Material(glm::vec3(0.05f, 0.05f, 0.0f), 0, 0, .078125f * 50);
			break;
		default:
			break;
		}

		return mat;
	}
}