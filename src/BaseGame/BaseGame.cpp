#include "BaseGame.h"

#include <GL/glew.h>
#include <glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer/Renderer.h"
#include "Window/_window.h"

#include "VertexBuffer/VertexBuffer.h"
#include "VertexBufferLayout/VertexBufferLayout.h"
#include "IndexBuffer/IndexBuffer.h"
#include "VertexArray/VertexArray.h"
#include "Shader/Shader.h"
#include "Texture/Texture.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"



namespace Engine
{
	glm::vec3 newCameraFront;
	Mouse* mouse;

	Engine::base_game::base_game(int Width, int Height)
		: m_Proj(glm::perspective(glm::radians(45.0f), (float)Width / (float)Height, 0.1f, 5000.0f)),
		m_View(glm::lookAt(glm::vec3(-300, -100, -800), glm::vec3(-300, -100, -800) + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)))
	{
		firstPersonCamera = new FirstPersonCamera(glm::vec3(-300, -100, -800), m_Proj, m_View);

		width = Width;
		height = Height;
		mouse = new Mouse((float)width / 2, (float)height / 2);
	}

	void base_game::Init(int Width, int Height, const char* name)
	{
		/* Initialize the library */
		if (!glfwInit())
			glfwTerminate();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode _window and its OpenGL context */
		myWindow = new window(Width, Height, name, NULL, NULL);

		if (!myWindow->get())
		{
			glfwTerminate();
		}

		/* Make the _window's context current */
		myWindow->makeContextCurrent(myWindow->get());

		glfwSwapInterval(1);

		std::cout << glGetString(GL_VERSION) << std::endl;

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		//-----------------------------------------------------------------

		m_Shader = std::make_unique<Shader>("../res/shaders/Basic.shader");

		for (std::list<Shape*>::iterator it = shapeList.begin(); it != shapeList.end(); ++it)
		{
			(*it)->SetTexturePath();
		}

		glfwSetInputMode(myWindow->get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(myWindow->get(), mouse_callback);
	}
	void base_game::Draw()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		{
			for (std::list<Shape*>::iterator it = shapeList.begin(); it != shapeList.end(); ++it)
			{
				(*it)->Draw();
				glm::mat4 mvp = firstPersonCamera->perspective * firstPersonCamera->view * (*it)->GetModel();
				m_Shader->Bind();
				m_Shader->SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(*(*it)->m_VAO, *(*it)->m_IndexBuffer, *m_Shader);
			}
		}
	}
	void base_game::CreateShape(std::string Path)
	{
		Shape* shape = new Shape(-50, -50, 50, 50);
		shape->SetPos(glm::vec3(200, 200, 0));
		shape->SetPath(Path);
		shape->SetTexturePath();
		shape->SetRigidBody(false);
		shapeList.push_back(shape);
	}
	void base_game::CreateShape(std::string Path, float minX, float minY, float maxX, float maxY)
	{
		Shape* shape = new Shape(minX, minY, maxX, maxY);
		shape->SetPos(glm::vec3(200, 200, 0));
		shape->SetPath(Path);
		shape->SetTexturePath();
		shapeList.push_back(shape);
	}
	void base_game::CreateShape(std::string Path, float minX, float minY, float maxX, float maxY, bool RigidBody)
	{
		Shape* shape = new Shape(minX, minY, maxX, maxY);
		shape->SetRigidBody(RigidBody);
		shape->SetPos(glm::vec3(200, 200, 0));
		shape->SetPath(Path);
		shape->SetTexturePath();
		shapeList.push_back(shape);
	}
	void base_game::CreateShape(std::string Path, glm::vec3 m_Translation, bool RigidBody)
	{
		Shape* shape = new Shape(-50, -50, 50, 50);
		shape->SetRigidBody(RigidBody);
		shape->SetPos(m_Translation);
		shape->SetPath(Path);
		shape->SetTexturePath();
		shapeList.push_back(shape);
	}
	void base_game::CreateShape(std::string Path, glm::vec3 m_Translation, float minXAtlas, float maxXAtlas, float minYAtlas, float maxYAtlas)
	{
		Shape* shape = new Shape(-50, -50, 50, 50);
		shape->SetPos(m_Translation);
		shape->SetPath(Path);
		shape->SetTexturePath();
		shapeList.push_back(shape);
	}
	void base_game::CreateShape(std::string Path, glm::vec3 m_Translation, float minXAtlas, float maxXAtlas, float minYAtlas, float maxYAtlas, bool RigidBody)
	{
		Shape* shape = new Shape(-50, -50, 50, 50);
		shape->SetRigidBody(RigidBody);
		shape->SetPos(m_Translation);
		shape->SetPath(Path);
		shape->SetTexturePath();
		shapeList.push_back(shape);
	}
	void Engine::base_game::CreateShape(std::string Path, glm::vec3 m_Translation, int rows, int columns,
		int totalAnimations, bool RigidBody)
	{
		Shape* shape = new Shape(-50, -50, 50, 50);
		shape->SetRigidBody(RigidBody);
		shape->SetPos(m_Translation);
		shape->SetPath(Path);
		shape->rows = rows;
		shape->columns = columns;
		shape->totalAnimations = totalAnimations;
		shape->SetTexturePath();
		Animation* actualAnimation = new Animation(rows, columns, shape->GetWidth(), shape->GetHeight(), totalAnimations);
		shape->SetAnimation(actualAnimation);
		shapeList.push_back(shape);
	}
	void base_game::UpdateShapePos(int index, glm::vec3 m_Translation)
	{
		std::list<Shape*>::iterator it = shapeList.begin();
		std::advance(it, index);
		if (!collisionManager->CheckCollisions(*it, m_Translation))
			(*it)->SetPos(m_Translation);
	}
	Shape* base_game::GetShapeByIndex(int index)
	{
		std::list<Shape*>::iterator it = shapeList.begin();
		std::advance(it, index);
		return *it;
	}
	CollisionManager* base_game::GetCollisionManager()
	{
		return collisionManager;
	}
	void base_game::Play()
	{
		collisionManager->SetShapeList(shapeList);
		Renderer myRenderer;
		while (running)
		{
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			myRenderer.Clear();
			firstPersonCamera->SetFront(newCameraFront);
			Update();
			Draw();
			glfwSwapBuffers(myWindow->get());
			glfwPollEvents();
		}
		glfwTerminate();
	}

	void base_game::mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (mouse->firstMouse)
		{
			mouse->lastX = xpos;
			mouse->lastY = ypos;
			mouse->firstMouse = false;
		}

		float xoffset = xpos - mouse->lastX;
		float yoffset = mouse->lastY - ypos;
		mouse->lastX = xpos;
		mouse->lastY = ypos;

		float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		mouse->yaw += xoffset;
		mouse->pitch += yoffset;

		if (mouse->pitch > 89.0f)
			mouse->pitch = 89.0f;
		if (mouse->pitch < -89.0f)
			mouse->pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(mouse->yaw)) * cos(glm::radians(mouse->pitch));
		direction.y = sin(glm::radians(mouse->pitch));
		direction.z = sin(glm::radians(mouse->yaw)) * cos(glm::radians(mouse->pitch));

		newCameraFront = glm::normalize(direction);
	}
}