#include "game.h"
#include <iostream>

game::game()
{
	actualCam = nullptr;
	floor = nullptr;
	cubeowo = nullptr;
	cubeowo2 = nullptr;
	cubeowoLight = nullptr;
}

game::~game() = default;

void game::draw()
{
	floor->draw();
	cubeowo->draw();
	cubeowo2->draw();
	cubeowoLight->draw();
}

void game::update()
{
	glm::vec3 movement = glm::vec3(0, 0, 0);

	glm::vec3 front = glm::normalize(actualCam->getFront() - actualCam->getPos());
	front.y = 0;

	const glm::vec3 up = glm::normalize(actualCam->getUp());
	const float boxSpeed = 1;


	if (isKeyPressed(ENGINE_KEY_ESCAPE))
	{
		close();
	}

	if (isKeyPressed(ENGINE_KEY_UP))
	{
		movement += front * boxSpeed;
	}
	else if (isKeyPressed(ENGINE_KEY_DOWN))
	{
		movement -= front * boxSpeed;
	}
	
	if (isKeyPressed(ENGINE_KEY_LEFT))
	{
		movement -= glm::normalize(glm::cross(front, up));
	}
	else if (isKeyPressed(ENGINE_KEY_RIGHT))
	{
		movement += glm::normalize(glm::cross(front, up));
	}

	cubeowo->setPos(cubeowo->getPos() + movement);
	cubeowoLight->setPos(cubeowoLight->getPos() + movement);

#pragma region CAMERA
	const float cameraMovementAmount = engine::time::getDeltaTime() * cameraSpeed;

	if (isKeyPressed(ENGINE_KEY_W))
	{
		actualCam->moveCamera(cameraMovementAmount, engine::MOVEMENT_DIRECTION::FRONT);
	}
	else if (isKeyPressed(ENGINE_KEY_S))
	{
		actualCam->moveCamera(cameraMovementAmount, engine::MOVEMENT_DIRECTION::BACK);
	}

	if (isKeyPressed(ENGINE_KEY_D))
	{
		actualCam->moveCamera(cameraMovementAmount, engine::MOVEMENT_DIRECTION::RIGHT);
	}
	else if (isKeyPressed(ENGINE_KEY_A))
	{
		actualCam->moveCamera(cameraMovementAmount, engine::MOVEMENT_DIRECTION::LEFT);
	}

	actualCam->rotateCamera(getMouseOffset());

	if (actualCam == thirdPersonCam)
	{
		thirdPersonCam->updateTargetPos(cubeowo->getPos());
	}
#pragma endregion
}

void game::init()
{
	const glm::vec3 camPos = { 20, 10, 30 };
	const glm::vec3 camView = { 0, 0, 0 };
	const glm::vec3 camUp = { 0, 1, 0 };

	firstPersonCam = new engine::firstPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	thirdPersonCam = new engine::thirdPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	actualCam = firstPersonCam;

	floor = new engine::sprite(currentRenderer, "../res/assets/textures/StoneFloorTexture.png", true, true);
	floor->setScale(glm::vec3(500, 500, 1));
	floor->setRot(glm::vec3(glm::radians(-90.0f), 0, 0));
	floor->setPos(glm::vec3(0,-5,0));

	cubeowo = new engine::shape(currentRenderer, engine::CUBE, true);
	cubeowo->setPos(0, 5, 0);
	cubeowo->setScale(5, 5, 5);
	cubeowo->setColor(glm::vec4(1.0f));

	cubeowo2 = new engine::shape(currentRenderer, engine::CUBE, true);
	cubeowo2->setPos(10, 5, 0);
	cubeowo2->setScale(5, 5, 5);
	cubeowo2->setColor(glm::vec4(1.0f));

	cubeowoLight = new engine::light(currentRenderer);
	cubeowoLight->setColor(glm::vec4(1.0f));

	changeClearColor(glm::vec4(0, 0, 0, 0));
}

void game::deInit()
{
	delete firstPersonCam;
	delete thirdPersonCam;

	floor->deinit();
	delete floor;

	delete cubeowo;
	delete cubeowo2;
	delete cubeowoLight;
}