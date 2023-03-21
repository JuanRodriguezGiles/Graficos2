#include "Renderer/Renderer.h"
#include "glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
int main(void)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode _window and its OpenGL context */
	window* myWindow = new window(800, 600, "Hello World", NULL, NULL);
	
	if (!myWindow->get())
	{
		glfwTerminate();
		return -1;
	}

	/* Make the _window's context current */
	myWindow->makeContextCurrent(myWindow->get());
	
	Renderer* myRenderer = new Renderer(myWindow);
	myRenderer->getShape()->setPos(glm::vec3(300, 200, 0.1f));
	
	myRenderer->getShape()->setScale(glm::vec3(30, 20, 1));
	/* Loop until the user closes the _window */
	while (!myWindow->windowShouldClose(myWindow->get()))
	{
		/* Render here */
		myRenderer->clearColor(GL_COLOR_BUFFER_BIT);
		glm::mat4 proj = glm::mat4(1.0f);
		proj = glm::ortho(0.0f, 600.0f, 0.0f, 400.0f, 0.1f, 100.0f);

		myRenderer->getShape()->setRot(glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 view = glm::mat4(1.0f);
		// note that we're translating the scene in the reverse direction of where we want to move
		view = glm::translate(view, glm::vec3(0,0, -3.0f));


		int projectionLoc = glGetUniformLocation(myRenderer->getShader(), "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(proj));

		int viewLoc = glGetUniformLocation(myRenderer->getShader(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int modelLoc = glGetUniformLocation(myRenderer->getShader(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(myRenderer->getShape()->getModel()));

		

		


		myRenderer->drawShape();
		
		/* Swap front and back buffers */
		myRenderer->swapBuffers(myWindow->get());
		
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}