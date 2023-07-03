#include "node.h"
#include <list>

namespace engine
{
	node::node()
	{

	}

	node::~node()
	{
	}

	vector<node*> node::getChildren()
	{
		return children;
	}

	int node::getChildrenAmount()
	{
		return children.size();
	}

	void node::draw()
	{
		_renderer->setMVP(model);

		for (int i = 0; i < meshes.size(); i++)
		{
			_renderer->drawMesh(meshes[i].vertices, meshes[i].indices, meshes[i].textures, meshes[i].VAO);
		}

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			children[i]->draw();
		}
	}

	void node::setRenderer(renderer* renderer)
	{
		_renderer = renderer;

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			children[i]->setRenderer(renderer);
		}
	}

	void node::setMeshes(vector<Mesh> meshes)
	{
		this->meshes = meshes;
	}

	void node::setName(string name)
	{
		this->name = name;
	}

	void node::setChildren(vector<node*> children)
	{
		this->children = children;
	}

	string node::getName()
	{
		return name;
	}

	node* node::getChildWithName(string name)
	{
		if (this->name == name)
		{
			return this;
		}

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			if (children[i]->getName() == name)
			{
				return children[i];
			}
		}

		for (int i = 0; i < getChildrenAmount(); i++)
		{
			node* node = children[i]->getChildWithName(name);

			if (node != NULL)
			{
				return node;
			}
		}

		return NULL;
	}

	void node::setParent(node* parent)
	{
		this->parent = parent;
	}

	void node::deinit()
	{
		for (int i = 0; i < getChildrenAmount(); i++)
		{
			children[i]->deinit();
			delete children[i];
		}
	}
}