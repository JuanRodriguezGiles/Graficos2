#pragma once
#include "Engine/baseGame.h"

class game : public engine::baseGame
{
public:
	game();
	~game() override;
	void update() override;
	void draw() override;
	void init() override;
	void deInit() override;

private:
	engine::entity* currentObject;

	engine::sprite* floor;

	engine::shape* cubeowo;
	engine::shape* cubeowo2;
	engine::shape* cubeowo3;
	engine::sprite* cubeowo4;

	engine::pointLight* pointLight[4];
	engine::directionalLight* directionalLight;
	engine::spotLight* spotLight;

	engine::camera* actualCam;
	engine::firstPersonCamera* firstPersonCam;
	engine::thirdPersonCamera* thirdPersonCam;

	const float cameraSpeed = 2;
	glm::vec3 currentObjectPos = glm::vec3(0, 0, 0);
};