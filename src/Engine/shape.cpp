#include "shape.h"
#include "renderer.h"
#include "glew.h"
#include "glfw3.h"

namespace engine
{
	shape::shape(renderer* render, unsigned int vert)
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;
		_renderer = render;

		float* vertex;
		unsigned int* indices;

		if(vert == 3)
		{
			vertex = new float[18]
			{
				-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
			};
			indices = new unsigned int[3]
			{
				0, 1, 2
			};
			_renderer->createBaseBuffer(VAO, VBO, EBO);
			_renderer->bindBaseBufferRequest(VAO, VBO, EBO, vertex, sizeof(vertex) * 18, indices, sizeof(indices) * 3);
			_vertices = 3;

			delete[] vertex;
			delete[] indices;
		}
		else if(vert == 4)
		{
			vertex = new float[24]
			{
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
			};
			indices = new unsigned int[6]
			{
				0, 1, 3,
				1, 2, 3
			};
			_renderer->createBaseBuffer(VAO, VBO, EBO);
			_renderer->bindBaseBufferRequest(VAO, VBO, EBO, vertex, sizeof(vertex) * 24, indices, sizeof(indices) * 6);
			_vertices = 6;

			delete[] vertex;
			delete[] indices;
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
		_renderer->solidShader.use();
		setShader();
		_renderer->drawRequest(model, VAO, _vertices, _renderer->solidShader.ID);
	}

	void shape::setShader()
	{
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		unsigned int colorLoc = glGetUniformLocation(_renderer->solidShader.ID, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(_renderer->solidShader.ID, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));
	}
}