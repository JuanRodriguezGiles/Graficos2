#include "renderer.h"
#include "light.h"
#include <string>
//#include "glew.h"
//#include "glfw3.h"
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

using namespace std;
using namespace glm;

namespace engine
{
	renderer::renderer()
	{
		currentWindow = NULL;
		viewMatrix = mat4();
		projectionMatrix = mat4();
		clearColor = vec4(0, 0, 0, 1);
	}
	renderer::renderer(window* window)
	{
		clearColor = vec4(0, 0, 0, 1);

		currentWindow = window;

		viewMatrix = mat4(1.0f);
		projectionMatrix = mat4(1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);
		//glFrontFace(GL_CCW);
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
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pointLightIndex = 0;
	}
	void renderer::endDraw()
	{
		shader.use();

		unsigned int initializedPointLightsLoc = glGetUniformLocation(shader.ID, "initializedPointLights");
		glUniform1i(initializedPointLightsLoc, pointLightIndex);

		glfwSwapBuffers(currentWindow->getGLFWwindow());
	}
	glm::mat4 renderer::GetViewMatrix()
	{
		return viewMatrix;
	}
	glm::mat4 renderer::GetProjMatrix()
	{
		return projectionMatrix;
	}
	void renderer::setShaderInfo(glm::vec4 color, unsigned int textures[], MATERIAL material)
	{
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);

		unsigned int colorLoc = glGetUniformLocation(shader.ID, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(shader.ID, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));

		Material materialValue = GetMaterialData(material);

		int diffuse = 0;
		int specular = 1;

		unsigned int textureLoc = glGetUniformLocation(shader.ID, "ourTexture");
		glUniform1f(textureLoc, (GLfloat)textures[0]);

		unsigned int materialLoc = glGetUniformLocation(shader.ID, "material.diffuse1");
		glUniform1i(materialLoc, diffuse);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		materialLoc = glGetUniformLocation(shader.ID, "material.specular1");
		glUniform1i(materialLoc, specular);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);

		materialLoc = glGetUniformLocation(shader.ID, "material.shininess");
		glUniform1fv(materialLoc, 1, &(materialValue.shininess));
	}
	void renderer::drawRequest(glm::mat4 modelMatrix, unsigned int VAO, unsigned int vertices)
	{
		setMVP(modelMatrix);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
	}
	void renderer::drawMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, unsigned int VAO, glm::vec3 color)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;

		unsigned int colorLoc = glGetUniformLocation(shader.ID, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(color));

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			string number;
			string name = textures[i].type;
			if (name == "texture_diffuse")
			{
				number = std::to_string(diffuseNr++);
				name = "diffuse";
			}
			else if (name == "texture_specular")
			{
				number = std::to_string(specularNr++);
				name = "specular";
			}

			shader.setFloat(("material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);

		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	void renderer::setMVP(glm::mat4 modelMatrix)
	{
		unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		unsigned int projectionLoc = glGetUniformLocation(shader.ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	}
	void renderer::processLight(glm::vec3 lightColor, glm::vec3 lightPos)
	{
		unsigned int lightColorLoc = glGetUniformLocation(shader.ID, "lightColor");
		glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

		unsigned int ambientStengthLoc = glGetUniformLocation(shader.ID, "ambientStrength");
		glUniform1fv(ambientStengthLoc, 1, &(ambientLight));

		unsigned int lightPosLoc = glGetUniformLocation(shader.ID, "lightPos");
		glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
	}
	void renderer::processDirectionalLight(glm::vec3 direction, Light light)
	{
		unsigned int lightInitializedLoc = glGetUniformLocation(shader.ID, "directionalLightInitialized");
		glUniform1i(lightInitializedLoc, true);

		unsigned int lightDirLoc = glGetUniformLocation(shader.ID, "dirLight.direction");
		glUniform3fv(lightDirLoc, 1, glm::value_ptr(direction));

		unsigned int lightAmbientLoc = glGetUniformLocation(shader.ID, "dirLight.ambient");
		glUniform3fv(lightAmbientLoc, 1, glm::value_ptr(light.ambient));

		unsigned int lighDiffusetLoc = glGetUniformLocation(shader.ID, "dirLight.diffuse");
		glUniform3fv(lighDiffusetLoc, 1, glm::value_ptr(light.diffuse));

		unsigned int lightSpecularLoc = glGetUniformLocation(shader.ID, "dirLight.specular");
		glUniform3fv(lightSpecularLoc, 1, glm::value_ptr(light.specular));

		unsigned int lightColorLoc = glGetUniformLocation(shader.ID, "dirLight.color");
		glUniform3fv(lightColorLoc, 1, glm::value_ptr(light.color));
	}
	void renderer::processPointLight(float constant, float linear, float quadratic, glm::vec3 position, Light light)
	{
		unsigned int lightAmbientLoc;
		unsigned int lighDiffusetLoc;
		unsigned int lightSpecularLoc;
		unsigned int lightConstantLoc;
		unsigned int lightLinearLoc;
		unsigned int lightQuadraticLoc;
		unsigned int lightPosLoc;
		unsigned int lightColorLoc;

		switch (pointLightIndex)
		{
		case 0:
			lightAmbientLoc = glGetUniformLocation(shader.ID, "pointLights[0].ambient");
			lighDiffusetLoc = glGetUniformLocation(shader.ID, "pointLights[0].diffuse");
			lightSpecularLoc = glGetUniformLocation(shader.ID, "pointLights[0].specular");
			lightConstantLoc = glGetUniformLocation(shader.ID, "pointLights[0].constant");
			lightLinearLoc = glGetUniformLocation(shader.ID, "pointLights[0].linear");
			lightQuadraticLoc = glGetUniformLocation(shader.ID, "pointLights[0].quadratic");
			lightPosLoc = glGetUniformLocation(shader.ID, "pointLights[0].position");
			lightColorLoc = glGetUniformLocation(shader.ID, "pointLights[0].color");
			break;
		case 1:
			lightAmbientLoc = glGetUniformLocation(shader.ID, "pointLights[1].ambient");
			lighDiffusetLoc = glGetUniformLocation(shader.ID, "pointLights[1].diffuse");
			lightSpecularLoc = glGetUniformLocation(shader.ID, "pointLights[1].specular");
			lightConstantLoc = glGetUniformLocation(shader.ID, "pointLights[1].constant");
			lightLinearLoc = glGetUniformLocation(shader.ID, "pointLights[1].linear");
			lightQuadraticLoc = glGetUniformLocation(shader.ID, "pointLights[1].quadratic");
			lightPosLoc = glGetUniformLocation(shader.ID, "pointLights[1].position");
			lightColorLoc = glGetUniformLocation(shader.ID, "pointLights[1].color");
			break;
		case 2:
			lightAmbientLoc = glGetUniformLocation(shader.ID, "pointLights[2].ambient");
			lighDiffusetLoc = glGetUniformLocation(shader.ID, "pointLights[2].diffuse");
			lightSpecularLoc = glGetUniformLocation(shader.ID, "pointLights[2].specular");
			lightConstantLoc = glGetUniformLocation(shader.ID, "pointLights[2].constant");
			lightLinearLoc = glGetUniformLocation(shader.ID, "pointLights[2].linear");
			lightQuadraticLoc = glGetUniformLocation(shader.ID, "pointLights[2].quadratic");
			lightPosLoc = glGetUniformLocation(shader.ID, "pointLights[2].position");
			lightColorLoc = glGetUniformLocation(shader.ID, "pointLights[2].color");
			break;
		case 3:
			lightAmbientLoc = glGetUniformLocation(shader.ID, "pointLights[3].ambient");
			lighDiffusetLoc = glGetUniformLocation(shader.ID, "pointLights[3].diffuse");
			lightSpecularLoc = glGetUniformLocation(shader.ID, "pointLights[3].specular");
			lightConstantLoc = glGetUniformLocation(shader.ID, "pointLights[3].constant");
			lightLinearLoc = glGetUniformLocation(shader.ID, "pointLights[3].linear");
			lightQuadraticLoc = glGetUniformLocation(shader.ID, "pointLights[3].quadratic");
			lightPosLoc = glGetUniformLocation(shader.ID, "pointLights[3].position");
			lightColorLoc = glGetUniformLocation(shader.ID, "pointLights[3].color");
			break;
		default:
			lightAmbientLoc = glGetUniformLocation(shader.ID, "pointLights[0].ambient");
			lighDiffusetLoc = glGetUniformLocation(shader.ID, "pointLights[0].diffuse");
			lightSpecularLoc = glGetUniformLocation(shader.ID, "pointLights[0].specular");
			lightConstantLoc = glGetUniformLocation(shader.ID, "pointLights[0].constant");
			lightLinearLoc = glGetUniformLocation(shader.ID, "pointLights[0].linear");
			lightQuadraticLoc = glGetUniformLocation(shader.ID, "pointLights[0].quadratic");
			lightPosLoc = glGetUniformLocation(shader.ID, "pointLights[0].position");
			lightColorLoc = glGetUniformLocation(shader.ID, "pointLights[0].color");
			break;
		}

		pointLightIndex++;

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
		unsigned int lightInitializedLoc = glGetUniformLocation(shader.ID, "spotLightInitialized");
		glUniform1i(lightInitializedLoc, true);

		unsigned int lightDirLoc = glGetUniformLocation(shader.ID, "spotLight.direction");
		glUniform3fv(lightDirLoc, 1, glm::value_ptr(direction));

		unsigned int lightPosLoc = glGetUniformLocation(shader.ID, "spotLight.position");
		glUniform3fv(lightPosLoc, 1, glm::value_ptr(position));

		unsigned int lightCutOffLoc = glGetUniformLocation(shader.ID, "spotLight.cutOff");
		glUniform1fv(lightCutOffLoc, 1, &cutOff);

		unsigned int lightOuterCutOffLoc = glGetUniformLocation(shader.ID, "spotLight.outerCutOff");
		glUniform1fv(lightOuterCutOffLoc, 1, &outerCutOff);

		unsigned int lightConstantLoc = glGetUniformLocation(shader.ID, "spotLight.constant");
		glUniform1fv(lightConstantLoc, 1, &constant);

		unsigned int lightLinearLoc = glGetUniformLocation(shader.ID, "spotLight.linear");
		glUniform1fv(lightLinearLoc, 1, &linear);

		unsigned int lightQuadraticLoc = glGetUniformLocation(shader.ID, "spotLight.quadratic");
		glUniform1fv(lightQuadraticLoc, 1, &quadratic);

		unsigned int lightAmbientLoc = glGetUniformLocation(shader.ID, "spotLight.ambient");
		glUniform3fv(lightAmbientLoc, 1, glm::value_ptr(light.ambient));

		unsigned int lighDiffusetLoc = glGetUniformLocation(shader.ID, "spotLight.diffuse");
		glUniform3fv(lighDiffusetLoc, 1, glm::value_ptr(light.diffuse));

		unsigned int lightSpecularLoc = glGetUniformLocation(shader.ID, "spotLight.specular");
		glUniform3fv(lightSpecularLoc, 1, glm::value_ptr(light.specular));

		unsigned int lightColorLoc = glGetUniformLocation(shader.ID, "spotLight.color");
		glUniform3fv(lightColorLoc, 1, glm::value_ptr(light.color));
	}
	void renderer::createBaseBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}
	void renderer::createExtraBuffer(unsigned int& buffer, int size)
	{
		glGenBuffers(size, &buffer);
	}
	void renderer::bindBaseBufferRequest(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices, unsigned int sizeOfVertices, unsigned int* indices, unsigned int sizeOfIndices)
	{
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
		unsigned int viewPosLoc = glGetUniformLocation(shader.ID, "viewPos");
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