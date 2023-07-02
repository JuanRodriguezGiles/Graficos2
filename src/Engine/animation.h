#pragma once
#include "exports.h"
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "atlasConfig.h"

namespace engine
{
	struct textureData;

	class ENGINE_API animation
	{
	public:
		animation();
		~animation();
		void play();
		void stop();
		bool update();
		bool isPlaying();
		void repeatAnimation(bool active);
		void setAnimationSpeed(float speed);
		void setAnimationTimeBetweenFrames(float time);
		void setAnimationFullTime(float time);
		void setAnimation(textureData* animationAtlasData, int columns, int rows);
		void setAnimation(textureData* animationAtlasData, atlasCutConfig config);
		void addFrameToAnimation(int posX, int posY, int width, int height);
		unsigned int getTextureID();
		glm::vec2* getCurrentFramesCoordinates();
	private:
		std::vector<glm::vec2*> framesCoordinates;
		textureData* texture;
		int currentFrame = 0;
		float currentTime = 0;
		float timeBetweenFrames = 1.f;
		float animationSpeed = 1.f;
		bool repeat = false;
		bool playing = false;
	};
}