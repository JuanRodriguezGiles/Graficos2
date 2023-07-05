#ifndef NODE_H
#define NODE_H

#include "exports.h"
#include "entity.h"
#include <vector>
#include "renderer.h"
#include "shape.h"
#include "camera.h"
#include "aabb.h"
//#include "modelImporter.h"
#include <string>
#include "plane.h"

#define AMOUNT_BOUNDS 8

namespace engine
{
	class ENGINE_API node : public entity
	{
	public:
		node();
		~node();

		vector<node*> getChildren();
		int getChildrenAmount();

		void setRenderer(renderer* render);
		void setMeshes(vector<Mesh> meshes);
		void setName(string name);
		void setChildren(vector<node*> children);
		void setParent(node* parent);
		void setDrawThisFrame(bool drawThisFrame);
		bool checkVolumeOnSameSide(plane* plane, glm::vec3 camPos, bool draw);
		void drawPosition(glm::vec3 pos);

		void generateAABB();
		void updateAABBWithChildren(node* child);
		engine::aabb* getLocalVolume();
		engine::aabb* getVolume();

		string getName();
		vector<glm::vec3> getLocalAABB();

		float getRandomNumber(float min, float max);
		node* getChildWithName(string name);

		bool canDrawThisFrame();
		void updateVisualAABBPositions();

		void setTransformations();
		void addBoundsToVisualAABB(vector<glm::vec3> childAABB);
		void draw();
		void deinit();
	private:
		vector<node*> children;
		node* parent;

		vector<Mesh> meshes;
		string name;

		void setAABBView(vector<Mesh> meshes);

		vector<glm::vec3> aabb;
		vector<glm::vec3> localAABB;
		vector<glm::vec3> aabbPositions;

		engine::aabb* localVolume;
		engine::aabb* volume;

		shape* aabbShapes[AMOUNT_BOUNDS];

		bool drawThisFrame;
	};
}
#endif