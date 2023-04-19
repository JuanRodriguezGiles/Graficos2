#pragma once
#include "Engine/baseGame.h"

const int colorsArraySize = 8;

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

	engine::sprite* floor;
	engine::sprite* container[6];
	engine::shape* lightCube[6];
	engine::light* lightSource;

	engine::camera* actualCam;
	engine::firstPersonCamera* firstPersonCam;
	engine::thirdPersonCamera* thirdPersonCam;

	float cameraSpeed = 30.f;
	glm::vec3 boxPos = glm::vec3(0, 0, 0);
	glm::vec3 lightCubePos = glm::vec3(0, 0, 0);

};
