#ifndef TILEMAP_H
#define TILEMAP_H

#include "tile.h"
#include <string>

namespace engine
{
	class ENGINE_API tileMap {
	public:
		tileMap(renderer* render);
		~tileMap();

		const tile& tile(unsigned int uiId);
		void setTile(const engine::tile& rkTile);
		void setMapTileId(int layer, unsigned int uiCol, unsigned int uiRow, unsigned int uiId);

		void setDimensions(float width, float heigth);
		void setTileDimensions(float tileWidth, float tileHeigth);

		void setTexture(textureData* rkTexture);
		void draw();

		bool importTileMap(std::string filePath);
		bool checkCollision(entity2D& object);

		int getWidth();
		int getHeight();

		std::vector<engine::tile**> getTilesGrid();

	private:
		std::vector<engine::tile> tiles;
		std::vector<engine::tile**> tileMapGrid;

		unsigned int width;
		unsigned int height;

		float tileWidth;
		float tileHeight;

		textureData* texture;

		float imageWidth;
		float imageHeight;

		float convertedPosX;
		float convertedPosY;

		std::string imagePath;

		renderer* currentRender;
	};
}
#endif