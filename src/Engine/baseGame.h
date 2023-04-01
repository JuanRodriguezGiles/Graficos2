#pragma once
#include "exports.h"
#include "keycodes.h"
#include "time.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shape.h"
#include "sprite.h"
#include "camera.h"
#include "firstPersonCamera.h"
#include "thirdPersonCamera.h"
#include "camera.h"
#include "tileMap.h"


namespace engine
{

	class window;
	class renderer;
	class input;
	class collisionManager;

	class ENGINE_API baseGame
	{
	public:
		baseGame();
		~baseGame();
		// ~ ENGINE ~ Initializes the engine loops, being init(), update(), draw(), deInit(). 
		void play(int windowSizeX, int windowSizeY, const char* windowName);

		virtual void update() = 0;

		virtual void draw() = 0;

		virtual void init() = 0;

		virtual void deInit() = 0;

		// Input
		// ~ ENGINE ~  Returns true every frame the engine key is pressed. 
		bool isKeyPressed(int keycode);
		// ~ ENGINE ~  Returns true the first frame the engine key is down. 
		bool isKeyDown(int keycode);
		// ~ ENGINE ~ Returns the current mouse position relative to the screen size.
		glm::vec2 getMousePosition();
		// ~ ENGINE ~ Returns the difference in the mouse position sice last movement.
		glm::vec2 getMouseOffset();
		// General
		// ~ ENGINE ~  Changes screen clear color to the parameter float values. 
		void changeClearColor(glm::vec4 color);
		// ~ ENGINE ~  Returns a double corresponding to the current time since GLFW context started. 
		double getCurrentTime();

		// Lerp
		// ~ ENGINE ~  Lerps between two float values based on a t Value. 
		float lerp(float v0, float v1, float t);
		// ~ ENGINE ~  Lerps between two color values based on a t Value. 
		glm::vec4 lerp(glm::vec4 color1, glm::vec4 color2, float t);

		// Random
		// ~ ENGINE ~  Returns a random float between the minimun and the maximun value. 
		float getRandomNumber(float min, float max);
		// ~ ENGINE ~  Returns a random color value. 
		glm::vec4 getRandomColor();

		// Collision
		// ~ ENGINE ~  Activates collision on the given entity. 
		void addCollider(entity2D* entity, bool isStatic);
		// ~ ENGINE ~  Removes collision on the given entity. 
		void removeCollider(entity2D* entity);
		// ~ ENGINE ~  Check if given entity has collider. 
		bool hasCollider(entity2D* entity);
		// ~ ENGINE ~  Set's the call for the collision checking. 
		void updateCollisions(engine::tileMap* tileMap);
	protected:
		renderer* currentRenderer;
		
	private:
		bool init_Internal(int windowSizeX, int windowSizeY, const char* windowName);
		void deinit_Internal();
		window* currentWindow;
		input* currentInput;
		time* currentTimer;
		collisionManager* currentCollisionManager;
		bool windowExitEvent();
	};
}