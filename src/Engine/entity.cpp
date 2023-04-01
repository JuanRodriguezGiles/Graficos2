#include "entity.h"
#include "renderer.h"

namespace engine
{
	entity::entity()
	{
		_renderer = NULL;
		model = glm::mat4(1.0f);
		translate = glm::mat4(1.0f);
		rotateX = glm::mat4(1.0f);
		rotateY = glm::mat4(1.0f);
		rotateZ = glm::mat4(1.0f);			
		scale = glm::mat4(1.0f);

		v3pos = glm::vec3(0.0f);
		v3rot = glm::vec3(0.0f);
		v3scale = glm::vec3(1.0f);

		updateModelMatrix();

		setColor(glm::vec4(1.0f));
	}

	entity::~entity()
	{

	}

	void entity::updateModelMatrix()
	{
		model = translate * rotateX * rotateY * rotateZ * scale;
	}
	void entity::setPos(glm::vec3 pos)
	{
		v3pos = pos;
		translate = glm::translate(glm::mat4(1.0f), v3pos);
		updateModelMatrix();
	}
	void entity::setPos(float x, float y, float z)
	{
		setPos(glm::vec3(x, y, z));
	}
	void entity::setRot(glm::vec3 rot)
	{
		setRotX(rot.x);
		setRotY(rot.y);
		setRotZ(rot.z);
		updateModelMatrix();
	}
	void entity::setRot(float x, float y, float z)
	{
		setRotX(x);
		setRotY(y);
		setRotZ(z);
		updateModelMatrix();
	}
	void entity::setRotX(float x)
	{
		v3rot.x = x;
		glm::vec3 axis;

		axis[1] = axis[2] = 0.0f;
		axis[0] = 1.0f;

		rotateX = glm::rotate(glm::mat4(1.0f), x, axis);
	}
	void entity::setRotY(float y)
	{
		v3rot.y = y;
		glm::vec3 axis;

		axis[0] = axis[2] = 0.0f;
		axis[1] = 1.0f;

		rotateY = glm::rotate(glm::mat4(1.0f), y, axis);
	}
	void entity::setRotZ(float z)
	{
		v3rot.z = z;
		glm::vec3 axis;

		axis[0] = axis[1] = 0.0f;
		axis[2] = 1.0f;

		rotateZ = glm::rotate(glm::mat4(1.0f), z, axis);
	}
	void entity::setScale(glm::vec3 scale)
	{
		v3scale = scale;

		this->scale = glm::scale(glm::mat4(1.0f), v3scale);
		updateModelMatrix();
	}
	void entity::setScale(float x, float y, float z)
	{
		setScale(glm::vec3(x, y, z));
	}
	void entity::setColor(glm::vec4 color)
	{
		this->color = color;
	}
	void entity::setColor(float r, float g, float b, float a)
	{
		color = glm::vec4(r, g, b, a);
	}
	glm::vec4 entity::getColor()
	{
		return color;
	}
	glm::vec3 entity::getPos()
	{
		return v3pos;
	}
	glm::vec3 entity::getRot()
	{
		return v3rot;
	}
	glm::vec3 entity::getScale()
	{
		return v3scale;
	}
	void entity::invertX()
	{
		setRotY(-3.14169265f);
		updateModelMatrix();
	}
	void entity::invertY()
	{
		setRotZ(-3.14169265f);
		updateModelMatrix();
	}
	void entity::invertZ()
	{
		setRotX(-3.14169265f);
		updateModelMatrix();
	}
}