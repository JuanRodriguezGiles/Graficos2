#include "tile.h"

namespace engine
{
	tile::tile()
	{
		_id = 0;
		_walkable = false;
	}
	tile::tile(int id, bool walkable, renderer* render, const char* filePathImage, bool invertImage)
	{
		_id = id;
		_walkable = walkable;

		setTexture(render, filePathImage, invertImage);
	}
	tile::~tile() 
	{
	}
	bool tile::isWalkable() 
	{
		if (!_walkable)
			return false;

		else
			return true;
	}

	void tile::walkability(bool bWalkable) 
	{
		_walkable = bWalkable;
	}

	unsigned int tile::getId() 
	{
		return _id;
	}

	void tile::setId(unsigned int id) 
	{
		_id = id;
	}
}