#ifndef OCCLUSION_CULLING_H
#define OCCLUSION_CULLING_H

#include "exports.h"
#include "camera.h"
#include "plane.h"
#include <vector>

namespace engine
{
	class ENGINE_API OcclusionCulling
	{
	public:
		OcclusionCulling();
		~OcclusionCulling();

		static void Init(camera* cam);
		static void Update();

		static bool IsOnView(std::vector<glm::vec3> aabb);
		static void SetCamera(camera* camera);


		static plane up;
		static plane down;
		static plane left;
		static plane right;
		static plane front;
		static plane back;

	private:
		static camera* cam;

		static glm::vec3 pointBack;
		static glm::vec3 pointFront;
		static glm::vec3 pointTopLeft;
		static glm::vec3 pointTopRight;
		static glm::vec3 pointBottomLeft;
		static glm::vec3 pointBottomRight;
	};
}

#endif //!OCCLUSION_CULLING_H