#pragma once
#include "BaseGame/BaseGame.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
class Game: public Engine::base_game
{
private:
	float speed = 0;
	bool turn = false;
public:
	Game(int Width, int Height);
	~Game();
	void Update() override;
};