#include "entity2D.h"
#include "collisionManager.h"
#include <math.h>      
#include <algorithm>

using namespace std;

namespace engine
{
	entity2D::entity2D()
	{
		colManager = nullptr;
	}
	entity2D::~entity2D()
	{
		if (colManager != NULL) colManager->removeFromCollisionList(this);
	}
	void entity2D::setCollisionManager(collisionManager* colManager)
	{
		this->colManager = colManager;
	}
	collisionType entity2D::checkCollision(entity2D& target, float &xOverlap, float &yOverlap)
	{
		xOverlap = max(0.0f,
			min(getPos().x + fabs(getScale().x) / 2.0f, target.getPos().x + fabs(target.getScale().x) / 2.0f) -
			max(getPos().x - fabs(getScale().x) / 2.0f, target.getPos().x - fabs(target.getScale().x) / 2.0f));

		yOverlap = max(0.0f,
			min(getPos().y + fabs(getScale().y) / 2.0f, target.getPos().y + fabs(target.getScale().y) / 2.0f) -
			max(getPos().y - fabs(getScale().y) / 2.0f, target.getPos().y - fabs(target.getScale().y) / 2.0f));

		if (xOverlap != 0.0f && yOverlap != 0.0f)
		{
			if (xOverlap > yOverlap)
			{
				if (getPos().y < 0 && getPos().y < target.getPos().y || getPos().y > 0 && getPos().y < target.getPos().y)
				{
					return collisionType::up;
				}
				else if (getPos().y < 0 && getPos().y > target.getPos().y || getPos().y > 0 && getPos().y > target.getPos().y)
				{
					return collisionType::down;
				}
			}
			else
			{
				if (getPos().x < 0 && getPos().x < target.getPos().x || getPos().x > 0 && getPos().x < target.getPos().x)
				{
					return collisionType::right;
				}
				else if (getPos().x < 0 && getPos().x > target.getPos().x || getPos().x > 0 && getPos().x > target.getPos().x)
				{
					return collisionType::left;
				}
			}
		}

		return collisionType::none;
	}

	void entity2D::applyCollisionRestrictions(collisionType colType, float xOverlap, float yOverlap, bool halfOverlap)
	{
		float defYOverlap = halfOverlap ? yOverlap / 2 : yOverlap;
		float defXOverlap = halfOverlap ? xOverlap / 2 : xOverlap;

		switch (colType)
		{
		case engine::collisionType::up:
			setPos(getPos().x, getPos().y - defYOverlap, getPos().z);
			break;
		case engine::collisionType::down:
			setPos(getPos().x, getPos().y + defYOverlap, getPos().z);
			break;
		case engine::collisionType::left:
			setPos(getPos().x + defXOverlap, getPos().y, getPos().z);
			break;
		case engine::collisionType::right:
			setPos(getPos().x - defXOverlap, getPos().y, getPos().z);
			break;
		case engine::collisionType::none:
		default:
			break;
		}
	}
}