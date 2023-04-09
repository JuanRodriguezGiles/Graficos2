#include "renderer.h"

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
	void renderer::drawRequest(glm::mat4 modelMatrix, unsigned int VAO, unsigned int vertices, unsigned int usedShaderID)
	{
		//Uniform: special variables in shaders that can be set from the application and are constant across all vertices or fragments processed by the shader
		unsigned int modelLoc = glGetUniformLocation(usedShaderID, "model");
		//set the value of a 4x4 matrix uniform variable in a shader program.
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		unsigned int viewLoc = glGetUniformLocation(usedShaderID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		unsigned int projectionLoc = glGetUniformLocation(usedShaderID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		//vertex array is a collection of vertex attribute data that describes the properties of vertices in a mesh or object (pos color tex)
		//VAO container object that stores the state of a vertex array, including the bindings of vertex buffer objects (VBOs) that contain vertex attribute data
		//Bind == reuse the same vertex array across multiple draw calls without having to re-specify the same state every time
		glBindVertexArray(VAO);


		//render geometric primitives by specifying a list of indices that reference vertex data stored in VBO
		glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
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
	void renderer::setProjectionMatrix(glm::mat4 projectionMatrix)
	{
		this->projectionMatrix = projectionMatrix;
	}
	window* renderer::getCurrentWindow()
	{
		return currentWindow;
	}
}