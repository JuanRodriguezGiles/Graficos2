#pragma once
#include "BaseGame/BaseGame.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
class Game: public Engine::base_game
{
private:
	bool turn = false;
public:
	Game();
	~Game();
	void Update() override;
};