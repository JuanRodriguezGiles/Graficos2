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

		if(vert == 3) //Triangle
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
		else if(vert == 4) 	//Square
		{

			//Alloc memory, first 3 values pos - last 3 color
			//Arranged counter clockwise
			vertex = new float[24]
			{
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
			};
			//indices of the vertices to be used to draw two triangles that form the square
			indices = new unsigned int[6]
			{
				0, 1, 3,
				1, 2, 3
			};
			//Creates VAO VBO and EBO
			_renderer->createBaseBuffer(VAO, VBO, EBO);
			//Binds to openGL context and set vertex/index data
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

		//specifies the layout of a vertex attribute in a vertex buffer object
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		//tells openGL to use the previously configured attribute 
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
		//Set color variable in SolidFragment shader
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));
		//Set alpha variable in SolidFragment shader
		unsigned int alphaLoc = glGetUniformLocation(_renderer->solidShader.ID, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));
	}
}