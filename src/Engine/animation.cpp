#include "animation.h"
#include "glfw3.h"
#include "textureImporter.h"
#include <algorithm>
#include "time.h"

namespace engine
{
	animation::animation()
	{
		texture = nullptr;
	}
	animation::~animation()
	{
		for (unsigned int i = 0; i < framesCoordinates.size(); i++)
		{
			delete[] framesCoordinates[i];
		}
	}
	void animation::play()
	{
		playing = true;
	}
	void animation::stop()
	{
		playing = false;
	}
	bool animation::update()
	{
		currentTime += time::getDeltaTime() * animationSpeed;
		if(currentTime > timeBetweenFrames)
		{
			currentTime -= timeBetweenFrames;
			currentFrame++;
			if(currentFrame == framesCoordinates.size())
			{
				currentFrame = 0;
				if(repeat)
				{
					play();
				}
				else
				{
					stop();
				}
			}
			return true;
		}
		return false;
	}
	bool animation::isPlaying()
	{
		return playing;
	}
	void animation::repeatAnimation(bool active)
	{
		repeat = active;
	}
	void animation::setAnimationSpeed(float speed)
	{
		animationSpeed = speed;
	}
	void animation::setAnimationTimeBetweenFrames(float time)
	{
		timeBetweenFrames = time;
	}
	void animation::setAnimationFullTime(float time)
	{
		animationSpeed = 1;
		timeBetweenFrames = time / framesCoordinates.size();
	}
	void animation::setAnimation(textureData* animationAtlasData, int columns, int rows)
	{
		texture = animationAtlasData;
		float spriteWidth = texture->width / columns;
		float spriteHeight = texture->height / rows;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{			
				glm::vec2* newCoord = new glm::vec2[4];
				newCoord[0].x = (spriteWidth + (spriteWidth * j)) / texture->width;			// top right
				newCoord[0].y = (spriteHeight * i) / texture->height;						// top right
				newCoord[1].x = (spriteWidth + (spriteWidth * j)) / texture->width; 		// bottom right
				newCoord[1].y = (spriteHeight + (spriteHeight * i)) / texture->height;		// bottom right
				newCoord[2].x = (spriteWidth * j) / texture->width;							// bottom left
				newCoord[2].y = (spriteHeight + (spriteHeight * i)) / texture->height;		// bottom left
				newCoord[3].x = (spriteWidth * j) / texture->width;							// top left 
				newCoord[3].y = (spriteHeight * i) / texture->height;						// top left 
				framesCoordinates.push_back(newCoord);
			}
		}
	}
	void animation::setAnimation(textureData* animationAtlasData, atlasCutConfig config)
	{
		texture = animationAtlasData;
		int spriteWidth = 0;
		int spriteHeight = 0;
		if(config.useSize)
		{
			spriteWidth = config.spriteWidth;
			spriteHeight = config.spriteHeight;
		}
		else
		{
			spriteWidth = (int)(texture->width / config.columns);
			spriteHeight = (int)(texture->height / config.rows);
		}
		int framesCount = 0;
		int x = config.offsetX;
		for (int i = config.offsetY; i < config.rows; i++)
		{
			while(x < config.columns)
			{
				glm::vec2* newCoord = new glm::vec2[4];
				newCoord[0].x = (spriteWidth + (spriteWidth * x)) / texture->width;			// top right
				newCoord[0].y = (spriteHeight * i) / texture->height;						// top right
				newCoord[1].x = (spriteWidth + (spriteWidth * x)) / texture->width; 		// bottom right
				newCoord[1].y = (spriteHeight + (spriteHeight * i)) / texture->height;		// bottom right
				newCoord[2].x = (spriteWidth * x) / texture->width;							// bottom left
				newCoord[2].y = (spriteHeight + (spriteHeight * i)) / texture->height;		// bottom left
				newCoord[3].x = (spriteWidth * x) / texture->width;							// top left 
				newCoord[3].y = (spriteHeight * i) / texture->height;						// top left 
				framesCoordinates.push_back(newCoord);
				framesCount++;
				x++;
				if (framesCount == config.framesAmount) return;
			}
			x = 0;
		}
	}
	void animation::addFrameToAnimation(int posX, int posY, int spriteWidth, int spriteHeight)
	{
		glm::vec2* newCoord = new glm::vec2[4];
		newCoord[0].x = (spriteWidth + (spriteWidth * posX)) / texture->width;			// top right
		newCoord[0].y = (spriteHeight * posY) / texture->height;						// top right
		newCoord[1].x = (spriteWidth + (spriteWidth * posX)) / texture->width; 			// bottom right
		newCoord[1].y = (spriteHeight + (spriteHeight * posY)) / texture->height;		// bottom right
		newCoord[2].x = (spriteWidth * posX) / texture->width;							// bottom left
		newCoord[2].y = (spriteHeight + (spriteHeight * posY)) / texture->height;		// bottom left
		newCoord[3].x = (spriteWidth * posX) / texture->width;							// top left 
		newCoord[3].y = (spriteHeight * posY) / texture->height;						// top left 
		framesCoordinates.push_back(newCoord);
	}
	unsigned int animation::getTextureID()
	{
		return texture->ID;
	}
	glm::vec2* animation::getCurrentFramesCoordinates()
	{
		return framesCoordinates[currentFrame];
	}
}
