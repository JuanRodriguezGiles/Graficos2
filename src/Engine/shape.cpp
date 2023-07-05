#include "shape.h"
#include "textureImporter.h"
#include "renderer.h"
//#include "glew.h"
//#include "glfw3.h"
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "vertexs.h"

namespace engine
{
	shape::shape(renderer* render, SHAPE shape, MATERIAL material)
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
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f

		};
		_renderer->createExtraBuffer(bufferPosUVs, 1);
		_renderer->bindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(3);
		setColor(glm::vec4(1));

		texture = new textureData(textureImporter::loadTexture("../res/assets/textures/defaultMaterial.png", false));
	}

	shape::~shape()
	{
		_renderer->deleteBaseBuffer(VAO, VBO, EBO);
		_renderer->deleteExtraBuffer(bufferPosUVs, 1);
		_renderer->deleteBaseBuffer(VAO, VBO, EBO);
		glDeleteTextures(1, &texture->ID);
		delete texture;
	}

	void shape::draw()
	{
		glBindTexture(GL_TEXTURE_2D, texture->ID);

		unsigned int textures[] = { texture->ID, texture->ID };

		_renderer->shader.use();
		_renderer->setShaderInfo(color, textures, material);
		_renderer->drawRequest(worldModel, VAO, _vertices);
	}

	void shape::draw(glm::mat4 worldModel)
	{
		glBindTexture(GL_TEXTURE_2D, texture->ID);

		unsigned int textures[] = { texture->ID, texture->ID };

		_renderer->shader.use();
		_renderer->setShaderInfo(color, textures, material);
		_renderer->drawRequest(worldModel, VAO, _vertices);
	}
}