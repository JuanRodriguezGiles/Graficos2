#ifndef PLANE_H
#define PLANE_H

#include "exports.h"
#include "GLM/glm.hpp"

namespace engine
{
	class ENGINE_API plane
	{
	public:
		plane();
		plane(glm::vec3 normal, glm::vec3 point);
		plane(glm::vec3 normal, float distance);
		plane(glm::vec3 a, glm::vec3 b, glm::vec3 c);
		~plane();

		void SetNormal(glm::vec3 normal);
		void SetDistance(float distance);

		glm::vec3 GetNormal() const;
		float GetDistance();

		void SetPositionAndNormal(glm::vec3 point, glm::vec3 normal);
		void Set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c);

		void Flip();
		void Translate(glm::vec3 translation);

		glm::vec3 ClosestPointOnPlane(glm::vec3 point);
		float GetDistanceToPoint(glm::vec3 point);

		bool GetSide(glm::vec3 point);
		bool SameSide(glm::vec3 point1, glm::vec3 point2);

	private:
		glm::vec3 normal;
		float distance;
	};
}

#endif // !PLANE_H