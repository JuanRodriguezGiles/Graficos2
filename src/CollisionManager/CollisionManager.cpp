#include "CollisionManager.h"
namespace Engine
{
	std::list<Shape*> CollisionManager::GetShapeList()
	{
		return shapeList;
	}

	void CollisionManager::SetShapeList(std::list<Shape*> ShapeList)
	{
		shapeList = ShapeList;
	}

	bool CollisionManager::CheckCollisions(Shape* shapeToCollide,glm::vec3 m_Translation)
	{
		for (std::list<Shape*>::iterator it1 = shapeList.begin(); it1 != shapeList.end(); ++it1)
		{
			if (*it1 != shapeToCollide)
			{
				if (ShapeAreColliding(m_Translation, shapeToCollide, *it1)&& shapeToCollide->GetRigidBody()&& (*it1)->GetRigidBody()) {
					return true;
				}
			}
		}
		return false;
	}

	bool CollisionManager::ShapeAreColliding(glm::vec3 m_Translation, Shape* shape1, Shape* shape2)
	{
		return m_Translation.x< shape2->GetPos().x+ shape2->GetWidth()&&
			m_Translation.x+ shape1->GetWidth()>shape2->GetPos().x&&
			m_Translation.y< shape2->GetPos().y + shape2->GetHeight() &&
			m_Translation.y + shape1->GetHeight()>shape2->GetPos().y;
	}

}
