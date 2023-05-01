#include "shape.h"
#include "renderer.h"
#include "glew.h"
#include "glfw3.h"
#include "vertexs.h"

namespace engine
{
	shape::shape(renderer* render, unsigned int vert, bool affectedByLight)
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;
		_renderer = render;
		this->affectedByLight = affectedByLight;

		if (vert == 3)
		{
			_renderer->createBaseBuffer(VAO, VBO, EBO);
			_renderer->bindBaseBufferRequest(VAO, VBO, EBO, GL::triangVertex, sizeof(GL::triangVertex) * GL::triangVertTam, GL::triangIndexes, sizeof(GL::triangIndexes) * GL::triangIndexTam);
			_vertices = GL::triangIndexTam;
		}
		else if (vert == 4)
		{
			_renderer->createBaseBuffer(VAO, VBO, EBO);
			_renderer->bindBaseBufferRequest(VAO, VBO, EBO, GL::quadVertex, sizeof(GL::quadVertex) * GL::triangVertTam, GL::quadIndexes, sizeof(GL::quadIndexes) * GL::quadIndexTam);
			_vertices = 6;
		}
		else if (vert == 8)
		{
			_renderer->createBaseBuffer(VAO, VBO, EBO);
			_renderer->bindBaseBufferRequest(VAO, VBO, EBO, GL::cubeVertex, sizeof(GL::cubeVertex) * GL::cubeVertTam, GL::cubeIndexes, sizeof(GL::cubeIndexes) * GL::cubeIndexTam);
			_vertices = GL::cubeIndexTam;
		}
		else
		{
			std::cout << vert << " Vertices amount not implemented." << std::endl;
			return;
		}

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

	}

	shape::~shape()
	{
		_renderer->deleteBaseBuffer(VAO, VBO, EBO);
	}

	void shape::draw()
	{
		_renderer->shaderPro.use();
		//setShader();
		_renderer->setShaderInfo(color, false, affectedByLight, 0);
		_renderer->drawRequest(model, VAO, _vertices);
	}

	//void shape::setShader()
	//{
	//	glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
	//	unsigned int colorLoc = glGetUniformLocation(_renderer->shaderPro.ID, "color");
	//	glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));
	//
	//	unsigned int alphaLoc = glGetUniformLocation(_renderer->shaderPro.ID, "a");
	//	glUniform1fv(alphaLoc, 1, &(color.a));
	//
	//	unsigned int affectedByLightLoc = glGetUniformLocation(_renderer->shaderPro.ID, "affectedByLight");
	//	glUniform1i(affectedByLightLoc, affectedByLight);
	//
	//	unsigned int usesTextureLoc = glGetUniformLocation(_renderer->shaderPro.ID, "usesTexture");
	//	glUniform1i(usesTextureLoc, false);
	//}
}