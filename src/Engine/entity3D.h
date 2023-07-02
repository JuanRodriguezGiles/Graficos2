#pragma once
#include "exports.h"
#include "entity.h"
#include <vector>
#include "renderer.h"
#include "modelImporter.h"
#include <string>

namespace engine
{
	class ENGINE_API entity3D : public entity
	{
	public:
		entity3D();
		entity3D(renderer* render, std::string path);
		~entity3D();
		void draw();
		void deinit();
	private:
		vector<Mesh> meshes;
	};
}