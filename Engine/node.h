#pragma once
#include "exports.h"
#include "entity.h"
#include <vector>
#include "renderer.h"
#include "modelImporter.h"
#include <string>

namespace engine
{
	class ENGINE_API node : public entity
	{
	public:
		node();
		node(renderer* render, std::string path);
		~node();
		vector<node>* getChildren();
		int getChildrenAmount();
		void draw();
		void deinit();
	private:
		vector<Mesh> meshes;
		vector<node>* children;
		node* parent;
	};
}	