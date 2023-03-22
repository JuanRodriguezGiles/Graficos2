#include "Game.h"

const float cameraSpeed = 1.0f; // adjust accordingly
glm::vec3 pos = glm::vec3(0, 0, 0);

Game::Game(int Width, int Height) : base_game(Width, Height)
{
	Width = 960;
	Height = 540;
	firstPersonCamera->UpdatePosition(glm::vec3(-300, -100, -800));
	firstPersonCamera->UpdateRotation(glm::vec3(0, 90, 0), 40);
	int zPos = 100;
	Init(Width, Height, "Test");
	CreateShape("../res/textures/background.png", glm::vec3(Width / 2, Height / 2, -50), false);
	CreateShape("../res/textures/guybush.png", glm::vec3(0, Height / 2, -50), 3, 6, 14, true);
	CreateShape("../res/textures/lechuck.png", glm::vec3(770, 200, -50), true);
	CreateShape("../res/textures/murray.png", glm::vec3(200, 300, -50), false);

	GetShapeByIndex(0)->SetScale(glm::vec3(9.6f, 5.4f, 1));
	GetShapeByIndex(1)->SetTime(0.3f);
	Play();
}
Game::~Game()
{
}
void Game::Update()
{
	if (GetShapeByIndex(2)->GetPos().x < 500) {
		turn = true;
	}
	else if (GetShapeByIndex(2)->GetPos().x > 770) {
		turn = false;
	}
	if (turn) {
		glm::vec3 nextPos = GetShapeByIndex(2)->GetPos();
		nextPos.x += 1;
		UpdateShapePos(2, nextPos);
	}
	else {
		glm::vec3 nextPos = GetShapeByIndex(2)->GetPos();
		nextPos.x -= 1;
		UpdateShapePos(2, nextPos);
	}

	if (glfwGetKey(myWindow->get(), GLFW_KEY_W) == GLFW_PRESS)
		pos -= cameraSpeed * firstPersonCamera->GetFront();
	if (glfwGetKey(myWindow->get(), GLFW_KEY_S) == GLFW_PRESS)
		pos += cameraSpeed * firstPersonCamera->GetFront();
	if (glfwGetKey(myWindow->get(), GLFW_KEY_A) == GLFW_PRESS)
		pos += glm::normalize(glm::cross(firstPersonCamera->GetFront(), firstPersonCamera->GetUp())) * cameraSpeed;
	if (glfwGetKey(myWindow->get(), GLFW_KEY_D) == GLFW_PRESS)
		pos -= glm::normalize(glm::cross(firstPersonCamera->GetFront(), firstPersonCamera->GetUp())) * cameraSpeed;

	firstPersonCamera->UpdatePosition(pos);

	if (glfwGetKey(myWindow->get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		running = false;
}