#include "entity.h"
//#include "renderer.h"

namespace engine
{
	entity::entity()
	{
		_renderer = NULL;
		worldModel = glm::mat4(1.0f);
		localModel = glm::mat4(1.0f);
		parentModel = glm::mat4(1.0f);
		localTranslate = glm::mat4(1.0f);
		localRotateX = glm::mat4(1.0f);
		localRotateY = glm::mat4(1.0f);
		localRotateZ = glm::mat4(1.0f);
		localScale = glm::mat4(1.0f);

		v3localPos = glm::vec3(0.0f);
		v3localRot = glm::vec3(0.0f);
		v3localScale = glm::vec3(1.0f);

		updateModelMatrix();

		setColor(glm::vec4(1.0f));

		useLocalMatrix = false;
	}

	entity::~entity()
	{

	}

	void entity::updateModelMatrix()
	{
		if (useLocalMatrix)
		{
			localModel = localTranslate * localRotateY * localRotateX * localRotateZ * localScale;
			worldModel = parentModel * localModel;
		}
		else
		{
			worldModel = localTranslate * localRotateY * localRotateX * localRotateZ * localScale;
		}
	}
	void entity::setPos(glm::vec3 pos)
	{
		v3localPos = pos;
		localTranslate = glm::translate(glm::mat4(1.0f), v3localPos);
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
		v3localRot.x = x;
		glm::vec3 axis;

		axis[1] = axis[2] = 0.0f;
		axis[0] = 1.0f;

		localRotateX = glm::rotate(glm::mat4(1.0f), x, axis);
	}
	void entity::setRotY(float y)
	{
		v3localRot.y = y;
		glm::vec3 axis;

		axis[0] = axis[2] = 0.0f;
		axis[1] = 1.0f;

		localRotateY = glm::rotate(glm::mat4(1.0f), y, axis);
	}
	void entity::setRotZ(float z)
	{
		v3localRot.z = z;
		glm::vec3 axis;

		axis[0] = axis[1] = 0.0f;
		axis[2] = 1.0f;

		localRotateZ = glm::rotate(glm::mat4(1.0f), z, axis);
	}
	void entity::setScale(glm::vec3 localScale)
	{
		v3localScale = localScale;
		this->localScale = glm::scale4(glm::mat4(1.0f), v3localScale);
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
	void entity::setWorldModelWithParentModel(glm::mat4 parentModel)
	{
		this->parentModel = parentModel;

		updateModelMatrix();
	}
	void entity::setLocalModel(glm::mat4 localModel)
	{
		float magnitude0 = glm::sqrt(localModel[0].x * localModel[0].x + localModel[0].y * localModel[0].y + localModel[0].z * localModel[0].z);
		float magnitude1 = glm::sqrt(localModel[1].x * localModel[1].x + localModel[1].y * localModel[1].y + localModel[1].z * localModel[1].z);
		float magnitude2 = glm::sqrt(localModel[2].x * localModel[2].x + localModel[2].y * localModel[2].y + localModel[2].z * localModel[2].z);

		setPos(localModel[3]);
		localModel[3].x = 0;
		localModel[3].y = 0;
		localModel[3].z = 0;
		setScale(glm::vec3(magnitude0, magnitude1, magnitude2));

		float theta1 = glm::atan(localModel[2].y, localModel[2].z);
		float c2 = glm::sqrt(localModel[0].x * localModel[0].x + localModel[1].x * localModel[1].x);
		float theta2 = glm::atan(-localModel[2].x, c2);
		float s1 = glm::sin(theta1);
		float c1 = glm::cos(theta1);
		float theta3 = glm::atan(s1 * localModel[0].z - c1 * localModel[0].y, c1 * localModel[1].y - s1 * localModel[1].z);
		glm::vec3 rotation = { -theta1, -theta2, -theta3 };

		setRot(rotation);

		this->localModel = localModel;
	}
	glm::vec4 entity::getColor()
	{
		return color;
	}
	glm::vec3 entity::getPos()
	{
		return v3localPos;
		//return worldModel[3];
	}
	glm::vec3 entity::getPosFromTransformMatrix()
	{
		return worldModel[3];
	}
	glm::vec3 entity::getRot()
	{
		return v3localRot;
	}
	glm::vec3 entity::getScale()
	{
		return v3localScale;
	}
	glm::mat4 entity::getModel()
	{
		return worldModel;
	}
	glm::mat4 entity::getLocalModel()
	{
		return localModel;
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
	void entity::UseLocalMatrix()
	{
		useLocalMatrix = true;
	}
}