#include "entity3D.h"

namespace engine
{
	entity3D::entity3D()
	{

	}

	entity3D::entity3D(renderer* render, std::string path)
	{
		_renderer = render;

		meshes = modelImporter::loadModel(path);
	}

	entity3D::~entity3D()
	{
	}

	void entity3D::draw()
	{
		_renderer->setMVP(model);

		for (int i = 0; i < meshes.size(); i++)
		{
			_renderer->drawMesh(meshes[i].vertices, meshes[i].indices, meshes[i].textures, meshes[i].VAO);
		}
	}

	void entity3D::deinit()
	{
	}
}