#pragma once
#include "Export.h"
#include "Window/_window.h"
#include "VertexBuffer/VertexBuffer.h"
#include "VertexBufferLayout/VertexBufferLayout.h"
#include "Texture/Texture.h"
#include  "Shape/Shape.h"
#include "CollisionManager/CollisionManager.h"
#include "Camera/Camera.h"
#include "Camera/FirstPersonCamera.h"
#include "Mouse/Mouse.h"
#include <memory>
namespace Engine
{
	class ENGINE_API base_game
	{
	public:
		window* myWindow = nullptr;
		base_game(int Width, int Height);
		void Play();
		void Init(int width, int height, const char* name);
		virtual void Update() = 0;
		void Draw();
		void DeInit();
		void CreateShape(std::string Path);
		void CreateShape(std::string Path, float minX, float minY, float maxX, float maxY);
		void CreateShape(std::string Path, float minX, float minY, float maxX, float maxY, bool RigidBody);
		void CreateShape(std::string Path, glm::vec3 m_Translation, bool RigidBody);
		void CreateShape(std::string Path, glm::vec3 m_Translation, float minXAtlas, float maxXAtlas, float minYAtlas, float maxYAtlas);
		void CreateShape(std::string Path, glm::vec3 m_Translation, float minXAtlas, float maxXAtlas, float minYAtlas, float maxYAtlas, bool RigidBody);
		void CreateShape(std::string Path, glm::vec3 m_Translation, int rows, int columns, int totalAnimations, bool RigidBody);
		void UpdateShapePos(int index, glm::vec3 m_Translation);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		void UpdatePos();
		Shape* GetShapeByIndex(int index);
		//Shape* GetShapeByName(std::string Name);
		CollisionManager* GetCollisionManager();
		bool running = true;
		FirstPersonCamera* firstPersonCamera;
		
	private:
		CollisionManager* collisionManager = new CollisionManager();
		int width;
		int height;
		std::list<Shape*> shapeList;
		std::unique_ptr<Shader> m_Shader;
		glm::mat4 m_Proj, m_View;
	protected:
	};
}