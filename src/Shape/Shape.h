#pragma once
#include "Entity/Entity.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "VertexBufferLayout/VertexBufferLayout.h"
#include"Texture/Texture.h"
#include "Animation/Animation.h"
#include <iostream>
#include "glfw3.h"
namespace Engine
{
	class ENGINE_API Shape : IEntity {
	private:
		glm::mat4 model = glm::mat4(1.0f);
		glm::vec3 m_translation;
		glm::vec4 m_rotation;
		glm::vec3 m_scale;
		std::string path;
		std::unique_ptr<Texture> m_Texture;
		Animation* animation;
		float time = 0;
		float width = 0;
		float height = 0;
		bool rigidbody = false;
		bool animationactive = false;
		glm::vec2 topRight = { 1,1 };
		glm::vec2 bottomRight = { 1,0 };
		glm::vec2 bottomLeft = { 0,0 };
		glm::vec2 topLeft = { 0,1 };
	public:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		int rows;
		int columns;
		int totalAnimations;
		Shape(float minX, float minY, float maxX, float maxY);
		glm::mat4 GetModel();
		bool IsAnimationRunning();
		void Animate(int currentRow, int totalFrames);
		void UpdateBuffer();
		void SetModel(glm::mat4 _model);
		void SetPath(std::string Path);
		void SetTexturePath();
		void Draw();
		void SetPos(glm::vec3 pos);
		void SetRot(glm::vec3 rot);
		void SetScale(glm::vec3 scale);
		void SetTime(float Time);
		void SetTexture(std::unique_ptr<Texture> m_Texture);
		void SetRigidBody(bool RigidBody);
		void SetAnimation(Animation* Animation);
		glm::vec3 GetPos();
		std::string GetPath();
		glm::vec4 GetRot();
		glm::vec3 GetScale();
		float GetTime();
		float GetWidth();
		float GetHeight();
		bool GetRigidBody();
		float positions[16];
		unsigned int indices[6];
		Animation* GetAnimation();
	};
}