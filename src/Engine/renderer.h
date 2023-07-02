#pragma once
#include "exports.h"
#include "window.h"
#include "shader.h"
#include <vector>
#include "light.h"
#include "Mesh.h"

namespace engine
{
	enum class MATERIAL
	{
		EMERALD,
		PEARL,
		BRONZE,
		GOLD,
		CYAN_PLASTIC,
		RED_PLASTIC,
		GREEN_RUBBER,
		YELLOW_RUBBER
	};

	struct Material {
		glm::vec3 ambient;
		int diffuse;
		int specular;
		float shininess;

		Material(glm::vec3 ambient, int diffuse, int specular, float shininess)
		{
			this->ambient = ambient;
			this->diffuse = diffuse;
			this->specular = specular;
			this->shininess = shininess;
		}

		Material()
		{

		}
	};

	class ENGINE_API renderer
	{
	public:
		renderer();
		renderer(window* window);
		~renderer();
		void setCurrentWindow(window* window);
		void createBaseBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void createExtraBuffer(unsigned int& buffer, int size);
		void bindBaseBufferRequest(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices, unsigned int sizeOfVertices, unsigned int* indices, unsigned int sizeOfIndices);
		void bindExtraBuffer(unsigned int buffer, float* data, unsigned int sizeOfData, unsigned int bufferType);
		void setShaderInfo(glm::vec4 color, unsigned int textures[], MATERIAL material);
		void drawRequest(glm::mat4 model, unsigned int VAO, unsigned int vertices);
		void setMVP(glm::mat4 modelMatrix);
		void drawMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, unsigned int VAO);
		void processLight(glm::vec3 lightColor, glm::vec3 lightPos);
		void processDirectionalLight(glm::vec3 direction, Light light);
		void processPointLight(float constant, float linear, float quadratic, glm::vec3 position, Light light);
		void processSpotLight(glm::vec3 direction, float constant, float linear, float quadratic, glm::vec3 position, Light light, float cutOff, float outerCutOff);
		void deleteBaseBuffer(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void deleteExtraBuffer(unsigned int& buffer, int size);
		void startDraw();
		void endDraw();
		void setClearColor(glm::vec4 color);
		void setViewMatrix(glm::mat4 viewMatrix);
		void setViewPosition(glm::vec3 viewPos);
		void setProjectionMatrix(glm::mat4 projectionMatrix);
		window* getCurrentWindow();

		glm::mat4 GetProjMatrix();
		glm::mat4 GetViewMatrix();

		Shader shader = Shader("../src/Engine/Shaders/TextureVertex.shader", "../src/Engine/Shaders/TextureFragment.shader");//Shader("../src/Motor/Shaders/TextureVertex.shader", "../src/Motor/Shaders/TextureFragment.shader");

	private:
		Material GetMaterialData(MATERIAL material);
		float lastTime = 0;
		float ambientLight = 0.1f;
		int pointLightIndex = 0;
		window* currentWindow;
		glm::vec4 clearColor;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};
}