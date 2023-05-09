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
	engine::sprite* floor;
	engine::shape* cubeowo;
	engine::shape* cubeowo2;
	engine::shape* cubeowo3;
	engine::light* cubeowoLight;

	engine::camera* actualCam;
	engine::firstPersonCamera* firstPersonCam;
	engine::thirdPersonCamera* thirdPersonCam;

	const float cameraSpeed = 30.f;
};