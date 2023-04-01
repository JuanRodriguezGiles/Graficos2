#pragma once
#include "exports.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace engine
{
	class renderer;

	class ENGINE_API entity
	{
	public:
		entity();
		~entity();
		void setPos(glm::vec3 pos);
		void setPos(float x, float y, float z);
		void setRot(glm::vec3 rot);
		void setRot(float x, float y, float z);
		void setScale(glm::vec3 scale);
		void setScale(float x, float y, float z);
		void setColor(glm::vec4 color);
		void setColor(float r, float g, float b, float a);
		void invertX();
		void invertY();
		void invertZ();
		
		glm::vec4 getColor();
		glm::vec3 getPos();
		glm::vec3 getRot();
		glm::vec3 getScale();

		virtual void draw() = 0;

	protected:
		renderer* _renderer;

		glm::vec3 v3pos;
		glm::vec3 v3rot;
		glm::vec3 v3scale;

		glm::mat4 model;

		glm::mat4 translate;
		glm::mat4 rotateX;
		glm::mat4 rotateY;
		glm::mat4 rotateZ;
		glm::mat4 scale;

		glm::vec4 color;

		unsigned int VAO, VBO, EBO, _vertices;
		
		void updateModelMatrix();
	private:
		void setRotX(float x);
		void setRotY(float y);
		void setRotZ(float z);
	};
}