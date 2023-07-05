#include "plane.h"

namespace engine
{
	plane::plane()
	{
		normal = glm::vec3();
		distance = 0.f;
	}

	plane::plane(glm::vec3 normal, glm::vec3 point)
	{
		this->normal = glm::normalize(normal);
		distance = -glm::dot(normal, point);
	}

	plane::plane(glm::vec3 normal, float distance)
	{
		this->normal = glm::normalize(normal);
		this->distance = distance;
	}

	plane::plane(glm::vec3 a, glm::vec3 b, glm::vec3 c)
	{
		normal = glm::normalize(glm::cross(b - a, c - a));
		distance = -glm::dot(normal, a);
	}

	plane::~plane()
	{
	}

	void plane::SetNormal(glm::vec3 normal)
	{
		this->normal = normal;
	}

	void plane::SetDistance(float distance)
	{
		this->distance = distance;
	}

	glm::vec3 plane::GetNormal() const
	{
		return normal;
	}

	float plane::GetDistance()
	{
		return distance;
	}

	void plane::SetPositionAndNormal(glm::vec3 point, glm::vec3 normal)
	{
		this->normal = glm::normalize(normal);
		distance = -glm::dot(this->normal, point);
	}

	void plane::Set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c)
	{
		normal = glm::normalize(glm::cross(b - a, c - a));
		distance = -glm::dot(normal, a);
	}

	void plane::Flip()
	{
		normal = -normal;
		distance = -distance;
	}

	void plane::Translate(glm::vec3 translation)
	{
		distance += glm::dot(normal, translation);
	}

	glm::vec3 plane::ClosestPointOnPlane(glm::vec3 point)
	{
		float pointToPlaneDistance = glm::dot(normal, point) + distance;
		return point - (normal * pointToPlaneDistance);
	}

	float plane::GetDistanceToPoint(glm::vec3 point)
	{
		return glm::dot(normal, point) + distance;
	}

	bool plane::GetSide(glm::vec3 point)
	{
		return glm::dot(normal, point) + distance > 0.f;
	}

	bool plane::SameSide(glm::vec3 point1, glm::vec3 point2)
	{
		float d0 = GetDistanceToPoint(point1);
		float d1 = GetDistanceToPoint(point2);
		return (d0 > 0.0f && d1 > 0.0f) || (d0 <= 0.0f && d1 <= 0.0f);
	}
}