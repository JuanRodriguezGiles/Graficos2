#include "game.h"

#include "Engine/modelImporter.h"

game::game()
{
	for (int i = 0; i < POINT_LIGHTS; i++)
	{
		pointLight[i] = nullptr;
		pointLightBox[i] = nullptr;
	}

	directionalLight = nullptr;
	spotLight = nullptr;
	spotLightBox = nullptr;


	backpackModel = nullptr;

	actualCam = nullptr;
}

game::~game()
{

}

void game::draw()
{
	for (int i = 0; i < POINT_LIGHTS; i++)
	{
		pointLight[i]->draw();
		pointLightBox[i]->draw();
	}

	spotLight->draw();
	spotLightBox->draw();

	
	directionalLight->draw();
	

	backpackModel->draw();

	floor->draw();
}

void game::update()
{
	if (isKeyPressed(ENGINE_KEY_0))
	{
		entityPos = pointLight[0]->getPos();
		selectedEntity = pointLight[0];
	}
	else if (isKeyPressed(ENGINE_KEY_1))
	{
		entityPos = pointLight[1]->getPos();
		selectedEntity = pointLight[1];
	}
	else if (isKeyPressed(ENGINE_KEY_2))
	{
		entityPos = pointLight[2]->getPos();
		selectedEntity = pointLight[2];
	}
	else if (isKeyPressed(ENGINE_KEY_3))
	{
		entityPos = pointLight[3]->getPos();
		selectedEntity = pointLight[3];
	}
	else if (isKeyPressed(ENGINE_KEY_4))
	{
		entityPos = spotLight->getPos();
		selectedEntity = spotLight;
	}
	else if (isKeyPressed(ENGINE_KEY_5))
	{
		entityPos = backpackModel->getPos();
		selectedEntity = backpackModel;
	}

	glm::vec3 rotation = selectedEntity->getRot();
	glm::vec3 movement = glm::vec3(0, 0, 0);
	glm::vec3 front = glm::vec3(0, 0, -1);
	glm::vec3 up = glm::vec3(0, 1, 0);

	float movementSpeed = 0.01f;
	float rotationSpeed = 1.0f;

	front.y = 0;

	if (isKeyPressed(ENGINE_KEY_UP))
	{
		movement += front * movementSpeed;
	}
	else if (isKeyPressed(ENGINE_KEY_DOWN))
	{
		movement -= front * movementSpeed;
	}

	if (isKeyPressed(ENGINE_KEY_LEFT))
	{
		movement -= glm::vec3(1, 0, 0) * movementSpeed;
	}
	else if (isKeyPressed(ENGINE_KEY_RIGHT))
	{
		movement += glm::vec3(1, 0, 0) * movementSpeed;
	}

	if (isKeyPressed(ENGINE_KEY_Q))
	{
		movement += up * movementSpeed;
	}
	else if (isKeyPressed(ENGINE_KEY_E))
	{
		movement -= up * movementSpeed;
	}

	if (isKeyPressed(ENGINE_KEY_I))
	{
		if (rotation.y > 0)
		{
			rotation.y -= engine::time::getDeltaTime() * rotationSpeed;

			rotation.y = rotation.y < 0 ? 0 : rotation.y;
		}
	}
	else if (isKeyPressed(ENGINE_KEY_O))
	{
		if (rotation.y < 360)
		{
			rotation.y += engine::time::getDeltaTime() * rotationSpeed;

			rotation.y = rotation.y > 360 ? 360 : rotation.y;
		}
	}

	if (isKeyPressed(ENGINE_KEY_K))
	{
		if (rotation.x > 0)
		{
			rotation.x -= engine::time::getDeltaTime() * rotationSpeed;

			rotation.x = rotation.x < 0 ? 0 : rotation.x;
		}
	}
	else if (isKeyPressed(ENGINE_KEY_L))
	{
		if (rotation.x < 360)
		{
			rotation.x += engine::time::getDeltaTime() * rotationSpeed;

			rotation.x = rotation.x > 360 ? 360 : rotation.x;
		}
	}

	entityPos += movement;
	
	selectedEntity->setPos(entityPos);
	selectedEntity->setRot(rotation);


	for (int i = 0; i < POINT_LIGHTS; i++)
	{
		pointLightBox[i]->setPos(pointLight[i]->getPos());
	}

	spotLightBox->setPos(spotLight->getPos());

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
		thirdPersonCam->updateTargetPos(backpackModel->getPos());
	}
}

void game::init()
{
	glm::vec3 camPos = { 0, 3, 2 };
	glm::vec3 camView = { 0, -1, 0 };
	glm::vec3 camUp = { 0, 1, 0 };
	firstPersonCam = new engine::firstPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	thirdPersonCam = new engine::thirdPersonCamera(currentRenderer, camPos, camView, camUp, engine::PROJECTION::PERSPECTIVE);
	actualCam = thirdPersonCam;

	currentRenderer->shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); 
	model = glm::scale4(model, glm::vec3(10.0f, 10.0f, 10.0f));	
	currentRenderer->shader.setMat4("model", model);

	backpackModel = engine::modelImporter::chargeBaseNodeInfo((string)"../res/assets/backpack/backpack.obj");
	backpackModel->setRenderer(currentRenderer);
	backpackModel->setRot(glm::vec3(glm::radians(-90.0f), 0, 0));

	floor = new engine::sprite(currentRenderer, "../res/assets/textures/StoneFloorTexture.png", "../res/assets/textures/StoneFloorTexture.png", true, engine::MATERIAL::YELLOW_RUBBER);
	floor->setScale(glm::vec3(10, 10, 1));
	floor->setRot(glm::vec3(glm::radians(-90.0f), 0, 0));
	floor->setPos(glm::vec3(0, 0, 0));

	for (int i = 0; i < POINT_LIGHTS; i++)
	{
		pointLight[i] = new engine::pointLight(currentRenderer);
		pointLight[i]->setColor(glm::vec4(1, 1, 1, 1));
		pointLight[i]->setPos(glm::vec3(-4 + 2 * i, 1, -3));

		pointLightBox[i] = new engine::shape(currentRenderer, engine::SHAPE::CUBE, static_cast<engine::MATERIAL>(i));
		pointLightBox[i]->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
		pointLightBox[i]->setPos(pointLight[i]->getPos());
	}

	pointLight[0]->setColor(glm::vec4(1, 0, 0, 1));
	pointLight[1]->setColor(glm::vec4(0, 1, 0, 1));
	pointLight[2]->setColor(glm::vec4(0, 0, 1, 1));
	pointLight[3]->setColor(glm::vec4(1, 1, 1, 1));

	directionalLight = new engine::directionalLight(currentRenderer);

	spotLight = new engine::spotLight(currentRenderer);
	spotLight->setPos({ 0,5,3 });
	spotLightBox = new engine::shape(currentRenderer, engine::SHAPE::CUBE, engine::MATERIAL::CYAN_PLASTIC);
	spotLightBox->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	spotLightBox->setPos(spotLight->getPos());

	selectedEntity = spotLight;
}

void game::deInit()
{
	delete firstPersonCam;
	delete thirdPersonCam;

	for (int i = 0; i < POINT_LIGHTS; i++)
	{
		delete pointLight[i];
		delete pointLightBox[i];
	}

	delete directionalLight;

	delete spotLight;
	delete spotLightBox;

	backpackModel->deinit();
	delete backpackModel;
}