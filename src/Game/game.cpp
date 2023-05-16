#include "game.h"
#include <iostream>

game::game()
{
	actualCam = nullptr;
	floor = nullptr;

	cubeowo = nullptr;
	cubeowo2 = nullptr;
	cubeowo3 = nullptr;
	cubeowo4 = nullptr;

	for (int i = 0; i < 4; i++)
	{
		pointLight[i] = nullptr;
	}
	directionalLight = nullptr;
	spotLight = nullptr;
}

game::~game() = default;

void game::draw()
{
	floor->draw();

	cubeowo->draw();
	cubeowo2->draw();
	cubeowo3->draw();
	cubeowo4->draw();
	
	for (int i = 0; i < 4; i++)
	{
		pointLight[i]->draw();
	}

	spotLight->draw();
	directionalLight->draw();
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
	const glm::vec3 camPos = { 0, 3, 2 };
	const glm::vec3 camView = { 0, 0, 0 };
	const glm::vec3 camUp = { 0, 1, 0 };

	firstPersonCam = new engine::firstPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	thirdPersonCam = new engine::thirdPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	actualCam = firstPersonCam;

	floor = new engine::sprite(currentRenderer, "../res/assets/textures/StoneFloorTexture.png", "../res/assets/textures/StoneFloorTexture.png",  true, engine::MATERIAL::CYAN_PLASTIC);
	floor->setScale(glm::vec3(10, 10, 1));
	floor->setRot(glm::vec3(glm::radians(-90.0f), 0, 0));
	floor->setPos(glm::vec3(0,0,0));

	cubeowo = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::YELLOW_RUBBER);
	cubeowo->setPos(0, 5, 0);
	cubeowo->setScale(2, 2, 2);
	cubeowo->setColor(glm::vec4(1.0f));

	cubeowo2 = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::BRONZE);
	cubeowo2->setPos(10, 5, 0);
	cubeowo2->setScale(2, 2, 2);
	cubeowo2->setColor(glm::vec4(1.0f));

	cubeowo3 = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::BRONZE);
	cubeowo3->setPos(20, 5, 0);
	cubeowo3->setScale(2, 2, 2);
	cubeowo3->setColor(glm::vec4(1.0f));

	cubeowo4 = new engine::sprite(currentRenderer, "../res/assets/textures/box.png", "../res/assets/textures/box_spec.png", true, engine::MATERIAL::PEARL);
	cubeowo4->setPos(glm::vec3(0, 7.5f, 10));
	cubeowo4->setScale(glm::vec3(10, 10, 10));
	cubeowo4->setRot(glm::vec3(glm::radians(-90.0f), 0, 0));

	for (int i = 0; i < 4; i++)
	{
		pointLight[i] = new engine::pointLight(currentRenderer, i);
		pointLight[i]->setColor(glm::vec4(1, 1, 1, 1));
		pointLight[i]->setPos(glm::vec3(-4 + 2 * i, 1, -3));
	}

	pointLight[0]->setColor(glm::vec4(1, 0, 0, 1));
	pointLight[1]->setColor(glm::vec4(0, 1, 0, 1));
	pointLight[2]->setColor(glm::vec4(0, 0, 1, 1));
	pointLight[3]->setColor(glm::vec4(1, 1, 1, 1));

	directionalLight = new engine::directionalLight(currentRenderer);

	spotLight = new engine::spotLight(currentRenderer);
	spotLight->setPos({ 0,5,3 });

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
	delete cubeowo3;

	cubeowo4->deinit();
	delete cubeowo4;

	for (int i = 0; i < 4; i++)
	{
		delete pointLight[i];
	}

	delete directionalLight;
}