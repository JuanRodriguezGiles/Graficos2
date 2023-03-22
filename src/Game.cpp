#include "Game.h"

const float cameraSpeed = 1.0f; // adjust accordingly
glm::vec3 pos = glm::vec3(0, 0, 0);

Game::Game(int Width, int Height) : base_game(Width, Height)
{
	Width = 960;
	Height = 540;
	
	camera->UpdatePosition(glm::vec3(-300, -100, -800));
	camera->UpdateRotation(glm::vec3(0, 90, 0), 40);
	
	Init(Width, Height, "Test");

	CreateShape("../res/textures/lechuck.png", glm::vec3(770, 200, -50), true);

	//camera->SetTarget(GetShapeByIndex(0)->GetPos());

	Play();
}

Game::~Game()
{
}

void Game::Update()
{
	if (glfwGetKey(myWindow->get(), GLFW_KEY_W) == GLFW_PRESS)
		pos -= cameraSpeed * camera->GetFront();
	if (glfwGetKey(myWindow->get(), GLFW_KEY_S) == GLFW_PRESS)
		pos += cameraSpeed * camera->GetFront();
	if (glfwGetKey(myWindow->get(), GLFW_KEY_A) == GLFW_PRESS)
		pos += glm::normalize(glm::cross(camera->GetFront(), camera->GetUp())) * cameraSpeed;
	if (glfwGetKey(myWindow->get(), GLFW_KEY_D) == GLFW_PRESS)
		pos -= glm::normalize(glm::cross(camera->GetFront(), camera->GetUp())) * cameraSpeed;

	camera->UpdatePosition(pos);

	if (glfwGetKey(myWindow->get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		running = false;
}