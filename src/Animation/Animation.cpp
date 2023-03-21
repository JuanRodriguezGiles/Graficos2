#include "Animation.h"
bool Animation::PlayAnimation(int totalColumns, int row, int cantAnimations, glm::vec2& topRight, glm::vec2& bottomRight, glm::vec2& bottomLeft, glm::vec2& topLeft)
{
	if (timer->getTime() <= timePerAnimation) {
		return false;
	}
	else {
		std::cout << animationIndex + (totalColumns * row) << std::endl;
		Frame* currentFrame = framesVector[animationIndex + (totalColumns * row)];

		topRight = currentFrame->topRight;
		bottomRight = currentFrame->bottomRight;
		bottomLeft = currentFrame->bottomLeft;
		topLeft = currentFrame->topLeft;

		if (animationIndex >= cantAnimations)
		{
			animationIndex = 0;
		}
		else
		{
			animationIndex++;
		}
		timer->reset();
	}
	return true;
}

Animation::Animation(int rows, int columns, float width, float height, int _totalAnimations)
{
	totalAnimations = _totalAnimations;
	timer->start();

	float spriteW = width / columns;
	float spriteH = height / rows;
	int counter = 0;

	for (int i = rows-1; i >= 0; i--)
	{
		for (int j = 0; j <columns ; j++)
		{
			glm::vec2 topRight;
			glm::vec2 bottomRight;
			glm::vec2 bottomLeft;
			glm::vec2 topLeft;

			bottomLeft.x = (spriteW * j) / width;
			bottomLeft.y = (spriteH * i) / height;

			bottomRight.x = (spriteW + (spriteW * j)) / width;
			bottomRight.y = (spriteH * i) / height;

			topRight.x = (spriteW + (spriteW * j)) / width;
			topRight.y = (spriteH + (spriteH * i)) / height;

			topLeft.x = (spriteW * j) / width;
			topLeft.y = (spriteH + (spriteH * i)) / height;

			Frame* newFrame = new Frame(topRight, bottomRight, bottomLeft, topLeft);
			framesVector.push_back(newFrame);

			counter++;
			if (counter == totalAnimations)
			{
				return;
			}
		}
	}
}

//Animation::Animation(float MinXAtlas, float MinYAtlas, float MaxXAtlas, float MaxYAtlas, float TimePerAnimation)
//{
//	timer->start();
//	timePerAnimation = TimePerAnimation;
//}

void Animation::SetAtlas(float MinXAtlas, float MinYAtlas, float MaxXAtlas, float MaxYAtlas)
{
}

void Animation::SetTime(float Time)
{
	time = Time;
}

Timer* Animation::GetTimer()
{
	return timer;
}

void Animation::SetTimePerAnimation(float TimePerAnimation)
{
	timePerAnimation = TimePerAnimation;
}
