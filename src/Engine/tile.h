#ifndef TILE_H
#define TILE_H

#include "sprite.h"

namespace engine
{
	class ENGINE_API tile : public sprite
	{
	public:
		tile();
		tile(int id, bool walkable, renderer* render, const char* filePathImage, bool invertImage);
		~tile();

		bool isWalkable();
		void walkability(bool bWalkable);

		unsigned int getId();
		void setId(unsigned int id);

	private:
		unsigned int _id;
		bool _walkable;
	};
}
#endif
