#ifndef NODE_H
#define NODE_H

#include "exports.h"
#include "entity.h"
#include <vector>
#include "renderer.h"
//#include "modelImporter.h"
#include <string>

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

		string getName();
		node* getChildWithName(string name);

		void draw();
		void deinit();
	private:
		vector<Mesh> meshes;

		vector<node*> children;
		node* parent;

		string name;
	};
}

#endif