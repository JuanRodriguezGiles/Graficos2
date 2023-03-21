#pragma once
#include "Shape/Shape.h"
namespace Engine
{
	class ENGINE_API CollisionManager {
	public:
		std::list<Shape*>GetShapeList();
		void SetShapeList(std::list<Shape*> ShapeList);
		bool CheckCollisions(Shape* shapeToCollide, glm::vec3 m_Translation);
		bool ShapeAreColliding(glm::vec3 m_Translation, Shape* shape1, Shape* shape2);
	private:
		std::list<Shape*> shapeList;
	};
}