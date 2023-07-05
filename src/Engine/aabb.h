#ifndef AABB_H
#define AABB_H

#include "exports.h"
#include <GLM/glm.hpp>
#include <vector>
#include "occlusionCulling.h"

using namespace std;

namespace engine
{
	class ENGINE_API volume
	{
	public:
		volume() { };
		~volume() { };

		virtual bool isOnFrustum(glm::mat4 worldModel) = 0;

	protected:
		virtual bool isOnPlane(plane plane) = 0;
	};

	class ENGINE_API aabb : public volume
	{
	public:
		aabb();
		aabb(glm::vec3 min, glm::vec3 max);
		aabb(glm::vec3 center, float extX, float extY, float extZ);
		~aabb();

		bool isOnFrustum(glm::mat4 worldModel) override;
		aabb getGlobalAABB(glm::mat4 worldModel);
		void update(glm::vec3 min, glm::vec3 max);

		glm::vec3 center;
		glm::vec3 extents;
		glm::vec3 min;
		glm::vec3 max;
		bool isOnPlane(plane plane) override;
	};
}

#endif