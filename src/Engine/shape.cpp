#include "shape.h"
#include "renderer.h"
#include "glew.h"
#include "glfw3.h"
#include "vertexs.h"

namespace engine
{
	shape::shape(renderer* render, SHAPE shape, bool affectedByLight, MATERIAL material)
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;
		_renderer = render;
		this->affectedByLight = affectedByLight;
		this->material = material;

		switch (shape)
		{
		case SHAPE::TRIANGLE:
		{
			_renderer->createBaseBuffer(VAO, VBO, EBO);
			_renderer->bindBaseBufferRequest(VAO, VBO, EBO, GL::triangVertex, sizeof(GL::triangVertex), GL::triangIndexes, sizeof(GL::triangIndexes));
			_vertices = GL::triangIndexTam;
		}
		break;
		case SHAPE::QUAD:
		{
			_renderer->createBaseBuffer(VAO, VBO, EBO);
			_renderer->bindBaseBufferRequest(VAO, VBO, EBO, GL::quadVertex, sizeof(GL::quadVertex), GL::quadIndexes, sizeof(GL::quadIndexes));
			_vertices = GL::quadIndexTam;
		}
		break;
		case SHAPE::CUBE:
		{
			_renderer->createBaseBuffer(VAO, VBO, EBO);
			_renderer->bindBaseBufferRequest(VAO, VBO, EBO, GL::cubeVertex, sizeof(GL::cubeVertex), GL::cubeIndexes, sizeof(GL::cubeIndexes));
			_vertices = GL::cubeIndexTam;
		}
		break;
		default:
		{
			std::cout << " Vertices amount not implemented." << std::endl;
			return;
		}
		break;
		}

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		float UVs[8] =
		{
			0.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 0.0f
		};
		_renderer->createExtraBuffer(bufferPosUVs, 1);
		_renderer->bindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(3);
		setColor(glm::vec4(1));
	}

	shape::~shape()
	{
		_renderer->deleteBaseBuffer(VAO, VBO, EBO);
		_renderer->deleteExtraBuffer(bufferPosUVs, 1);

		_renderer->deleteBaseBuffer(VAO, VBO, EBO);
	}

	void shape::draw()
	{
		_renderer->shaderPro.use();
		_renderer->setShaderInfo(color, false, affectedByLight, 0, material);
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