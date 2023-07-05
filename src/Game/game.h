#pragma once
#include "Engine/baseGame.h"

#define POINT_LIGHTS 4

class game : public engine::baseGame
{
public:
	game();
	~game();
	void update() override;
	void draw() override;
	void init() override;
	void deInit() override;
private:
	engine::sprite* floor;
	engine::pointLight* pointLight[POINT_LIGHTS];
	engine::shape* pointLightBox[POINT_LIGHTS];
	engine::directionalLight* directionalLight;
	engine::spotLight* spotLight;
	engine::shape* spotLightBox;
	
	engine::entity* selectedEntity;
	engine::node* model3d;
	engine::node* model3d2;

	engine::camera* actualCam;
	engine::firstPersonCamera* firstPersonCam;
	engine::thirdPersonCamera* thirdPersonCam;
	const float cameraSpeed = 2;
	glm::vec3 entityPos = glm::vec3(0, 0, 0);
	glm::vec3 entityRot = glm::vec3(0, 0, 0);
};