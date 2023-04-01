#pragma once
#include "exports.h"
#include "entity.h"

namespace engine
{
	class collisionManager;

	enum class collisionType { up, down, left, right, none };

	class ENGINE_API entity2D : public entity
	{
	public:
		entity2D();
		~entity2D();
		void setCollisionManager(collisionManager* colManager);
		collisionType checkCollision(entity2D& target, float& xOverlap, float& yOverlap);
		void applyCollisionRestrictions(collisionType colType, float xOverlap, float yOverlap, bool halfOverlap);
	private:
		collisionManager* colManager;
	};
}