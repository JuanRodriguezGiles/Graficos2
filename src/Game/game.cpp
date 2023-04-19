#include "game.h"
#include <iostream>

game::game()
{
	for (short i = 0; i < 6; i++)
	{
		container[i] = nullptr;
	}

	//awesomeface = nullptr;
	floor = nullptr;
	actualCam = nullptr;

	for (short i = 0; i < 6; i++)
	{
		lightSource[i] = nullptr;
	}
}

game::~game()
{

}

void game::draw()
{
	for (short i = 0; i < 6; i++)
	{
		container[i]->draw();
	}
	//awesomeface->draw();
	floor->draw();

	for (short i = 0; i < 6; i++)
	{
		lightSource[i]->draw();
	}
}

void game::update()
{
	if(isKeyPressed(ENGINE_KEY_ESCAPE))
	{
		close();
	}

	//box movement
	glm::vec3 movement = glm::vec3(0, 0, 0);
	glm::vec3 front = glm::normalize(actualCam->getFront() - actualCam->getPos());
	glm::vec3 up = glm::normalize(actualCam->getUp());
	float boxSpeed = 1;
	float boxFaces = 6;

	front.y = 0;

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

	for (short i = 0; i < boxFaces; i++)
	{
		container[i]->setPos(container[i]->getPos() + movement);
	}

	//awesomeface->setPos(awesomeface->getPos() + movement);

	boxPos += movement;

	//std::cout << "x: " << movement.x << " - y: " << movement.y << " - z: " << movement.z<< std::endl;

	//camera movement

	float cameraMovementAmount = engine::time::getDeltaTime() * cameraSpeed;

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
		thirdPersonCam->updateTargetPos(boxPos);
	}
		
	/* 
	
	PARA METER ROTACIÒN DE CAMARA PROXIMAMENTE

	if (isKeyPressed(ENGINE_KEY_K))
	{
		glm::vec3 rotation = { 0, 0, engine::time::getDeltaTime() * cameraSpeed };
	}
	else if (isKeyPressed(ENGINE_KEY_L))
	{
		glm::vec3 rotation = { 0, 0, engine::time::getDeltaTime() * -cameraSpeed };
	}
	
	*/
}

void game::init()
{
	glm::vec3 camPos = { 20, 10, 30 };
	glm::vec3 camView = { 0, 0, 0 };
	glm::vec3 camUp = { 0, 1, 0 };

	firstPersonCam = new engine::firstPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	thirdPersonCam = new engine::thirdPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	actualCam = firstPersonCam;

	/*if (tileMap->importTileMap("../res/assets/tilemapreal.tmx"))
	{
		std::cout << "tilemap loaded";
	}
	else
	{
		std::cout << "tilemap failed to load";
	}*/

	/*triangle = new engine::lightSource(currentRenderer, 3);
	triangle->setScale(3, 3, 3);
	triangle->setPos(-14, -10, 0);
	triangle->setColor(1, 1, 0, 1);

	triangle2 = new engine::lightSource(currentRenderer, 3);
	triangle2->setScale(3, 3, 3);
	triangle2->setPos(-17, -10, 0);
	triangle2->setColor(1, 1, 0, 1);

	triangle3 = new engine::lightSource(currentRenderer, 3);
	triangle3->setScale(3, 3, 3);
	triangle3->setPos(-15.5, -7, 0);
	triangle3->setColor(1, 1, 0, 1);

	quad = new engine::lightSource(currentRenderer, 4);
	quad->setScale(5, 5, 5);
	quad->setPos(15, -10, 0);
	quad->setColor(0, 1, 1, 1);

	imageCampus = new engine::sprite(currentRenderer, "../res/assets/textures/Image Campus.png", true);
	imageCampus->setScale(glm::vec3(30, 20, 10));
	imageCampus->setPos(glm::vec3(0, -9.f, -.1f));

	container = new engine::sprite(currentRenderer, "../res/assets/textures/container.jpg", true);
	container->setScale(glm::vec3(10, 10, 10));
	container->setPos(glm::vec3(-15, 0, 0));*/

	//awesomeface = new engine::sprite(currentRenderer, "../res/assets/textures/maxwell.png", true);
	//awesomeface->setScale(glm::vec3(10, 10, 10));

	for (short i = 0; i < 6; i++)
	{
		container[i] = new engine::sprite(currentRenderer, "../res/assets/textures/maxwell.png", true, true);
		container[i]->setScale(glm::vec3(10, 10, 10));

		lightSource[i] = new engine::shape(currentRenderer, 4, false);
		lightSource[i]->setScale(glm::vec3(5, 5, 5));
		lightSource[i]->setColor(glm::vec4(1, 0.1f, 0.1f, 1));
	}

	container[0]->setPos(glm::vec3(0, 0, 5));
	container[0]->setRot(glm::vec3(0, 0, 0));
	//awesomeface->setPos(glm::vec3(0, 0, 5.5f));
	//->setRot(glm::vec3(0, 0, 0));

	container[1]->setPos(glm::vec3(5, 0, 0));
	container[1]->setRot(glm::vec3(0, glm::radians(90.0f), 0));

	container[2]->setPos(glm::vec3(0, 0, -5));
	container[2]->setRot(glm::vec3(0, glm::radians(180.0f), 0));

	container[3]->setPos(glm::vec3(-5, 0, 0));
	container[3]->setRot(glm::vec3(0, glm::radians(-90.0f), 0));

	container[4]->setPos(glm::vec3(0, 5, 0));
	container[4]->setRot(glm::vec3(glm::radians(-90.0f), 0, 0));

	container[5]->setPos(glm::vec3(0, -5, 0));
	container[5]->setRot(glm::vec3(glm::radians(90.0f), 0, 0));

	boxPos = glm::vec3(0, 0, 0);

	floor = new engine::sprite(currentRenderer, "../res/assets/textures/StoneFloorTexture.png", true, true);
	floor->setScale(glm::vec3(500, 500, 1));
	floor->setRot(glm::vec3(glm::radians(-90.0f), 0, 0));
	floor->setPos(glm::vec3(0,-5,0));



	lightSourcePos = glm::vec3(12, 5, -5);


	lightSource[0]->setPos(glm::vec3(0, 0, 2.5f) + lightSourcePos);
	lightSource[0]->setRot(glm::vec3(0, 0, 0));

	lightSource[1]->setPos(glm::vec3(2.5f, 0, 0) + lightSourcePos);
	lightSource[1]->setRot(glm::vec3(0, glm::radians(90.0f), 0));

	lightSource[2]->setPos(glm::vec3(0, 0, -2.5f) + lightSourcePos);
	lightSource[2]->setRot(glm::vec3(0, glm::radians(180.0f), 0));

	lightSource[3]->setPos(glm::vec3(-2.5f, 0, 0) + lightSourcePos);
	lightSource[3]->setRot(glm::vec3(0, glm::radians(-90.0f), 0));

	lightSource[4]->setPos(glm::vec3(0, 2.5f, 0) + lightSourcePos);
	lightSource[4]->setRot(glm::vec3(glm::radians(-90.0f), 0, 0));

	lightSource[5]->setPos(glm::vec3(0, -2.5f, 0) + lightSourcePos);
	lightSource[5]->setRot(glm::vec3(glm::radians(90.0f), 0, 0));

	changeClearColor(glm::vec4(0, 0, 0, 0));
}

void game::deInit()
{
	delete firstPersonCam;
	delete thirdPersonCam;

	for (short i = 0; i < 6; i++)
	{
		container[i]->deinit();
		delete container[i];
		delete lightSource[i];
	}

	//awesomeface->deinit();
	//delete awesomeface;

	floor->deinit();
	delete floor;
}