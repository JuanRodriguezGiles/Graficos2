#pragma once
#include "Timer/timer.h"
#include "glm.hpp"
#include <vector>
#include <iostream>
#include "Frame/Frame.h"
class Animation {
private:
	Timer* timer = new Timer();
	float time = 0;
	float timePerAnimation = 0.1f;
	int totalAnimations = 0;
	int animationIndex = 0;
public:
	bool PlayAnimation(int totalColumns, int row, int cantAnimations, glm::vec2& topRight, glm::vec2& bottomRight, glm::vec2& bottomLeft, glm::vec2& topLeft);
	Animation(int rows, int columns, float width, float height, int _totalAnimations);
	void SetAtlas(float MinXAtlas, float MinYAtlas, float MaxXAtlas, float MaxYAtlas);
	void SetTime(float Time);
	Timer* GetTimer();
	void SetTimePerAnimation(float TimePerAnimation);
	std::vector<Frame*> framesVector;
};