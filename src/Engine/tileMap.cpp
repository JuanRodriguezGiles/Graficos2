#include "tileMap.h"
#include "tinyxml2.h"
#include "textureImporter.h"
#include <iostream>
//
#include <map>
#include <windows.h>
//
namespace engine
{
	//
	std::map<std::string, int> cmap = {
						{ "Black"       , 0  },
						{ "Blue"        , 1  },
						{ "Green"       , 2  },
						{ "Aqua"        , 3  },
						{ "Red"         , 4  },
						{ "Purple"      , 5  },
						{ "Yellow"      , 6  },
						{ "White"       , 7  },
						{ "Gray"        , 8  },
						{ "Light_Blue"  , 9  },
						{ "Light_Green" , 10 },
						{ "Light_Aqua"  , 11 },
						{ "Light_Red"   , 12 },
						{ "Light_Purple", 13 },
						{ "Light_Yellow", 14 },
						{ "Bright_White", 15 } };
	


	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


	void color(std::string s)
	{
		SetConsoleTextAttribute(h, cmap[s]);        // need to add some checking ... job for another day
	}
	//

	tileMap::tileMap(renderer* render)
	{
		currentRender = render;
	}

	tileMap::~tileMap() {}

	const tile& tileMap::tile(unsigned int uiId) {
		engine::tile* NoTile = nullptr;

		for (int i = 0; i < tiles.size(); i++) {
			if (uiId == tiles[i].getId()) {
				return tiles[i];
			}
		}

		return *NoTile;
	}

	void tileMap::setMapTileId(int layer, unsigned int uiCol, unsigned int uiRow, unsigned int uiId) 
	{
		tileMapGrid[layer][uiCol][uiRow] = tile(uiId);
	}

	void tileMap::setTile(const engine::tile& rkTile) 
	{
		tiles.push_back(rkTile);
	}

	void tileMap::setTileDimensions(float _tileWidth, float _tileHeight) 
	{
		tileWidth = _tileWidth;
		tileHeight = _tileHeight;
	}

	void tileMap::setDimensions(float _width, float _height) 
	{
		width = _width;
		height = _height;

		//creo la grilla bidimensional para guardar la posicion de cada tile igual que en el editor
		engine::tile** tileMap;
		tileMap = new engine::tile *[height];
		for (int i = 0; i < height; i++) {
			tileMap[i] = new engine::tile[width];
		}
		tileMapGrid.push_back(tileMap);
	}

	void tileMap::setTexture(textureData* rkTexture)
	{
		texture = rkTexture;
	}

	void tileMap::draw() 
	{
		//currentRender.setCurrentTexture(texture);

		float mapWidth = -(width * tileWidth) / 2.0f;
		float mapHeight = (height * tileHeight) / 2.0f;

		for (int i = 0; i < tileMapGrid.size(); i++) 
		{
			for (int y = 0; y < height; y++) 
			{
				for (int x = 0; x < width; x++) 
				{
					if (tileMapGrid[i][y][x].getId() != NULL) 
					{
						glm::vec3 pos = glm::vec3(mapWidth + (tileWidth * x), mapHeight - (tileHeight * y), 0);
						tileMapGrid[i][y][x].setPos(pos);
						//tileMapGrid[i][y][x].setPosX(mapWidth + (tileWidth * x));
						//tileMapGrid[i][y][x].setPosY(mapHeight - (tileHeight * y));
						tileMapGrid[i][y][x].draw();
					}
				}
			}
		}

	}

	bool tileMap::importTileMap(std::string filePath) {

		tinyxml2::XMLDocument doc; //guarda el documento
		tinyxml2::XMLError errorHandler; //guarda el resultado de las funciones

		errorHandler = doc.LoadFile(filePath.c_str()); //carga el archivo XML
		if (errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED) return false;

		// Loading Map element and save Map width, heigth in tiles and width, heigth of Tiles in pixels
		tinyxml2::XMLElement* mapNode = doc.FirstChildElement("map");
		if (mapNode == nullptr)
			return false;
		setDimensions(mapNode->FloatAttribute("width"), mapNode->FloatAttribute("height"));				// Get width and heigth for
		setTileDimensions(mapNode->FloatAttribute("tilewidth"), mapNode->FloatAttribute("tileheight")); // the map and the tiles

		// Loading Tilset element
		tinyxml2::XMLElement* pTileset = mapNode->FirstChildElement("tileset");
		if (pTileset == NULL)
			return false;

		int tileCount = pTileset->IntAttribute("tilecount"); // Number of Tiles in the Tileset
		int columns = pTileset->IntAttribute("columns");  // Columns of Tiles in the Tileset
		int rows = tileCount / columns;

		imagePath = "../res/assets/";																//
		imagePath += pTileset->FirstChildElement("image")->Attribute("source");			// Loading Textures
		textureData textData = textureImporter::loadTexture(imagePath.c_str(), true);
		setTexture(&textData);// D3DCOLOR_XRGB(255, 255, 255))); //

		// Save the Tiles in the TileMap
		imageWidth = pTileset->FirstChildElement("image")->IntAttribute("width");
		imageHeight = pTileset->FirstChildElement("image")->IntAttribute("height");
		float tileX = 0.0f, tileY = 0.0f;
		int _id = 1;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				engine::tile newTile;

				newTile.setId(_id);
				newTile.setTexture(currentRender, imagePath.c_str(), imagePath.c_str(), false);
				newTile.setScale(glm::vec3(tileWidth, tileHeight,1.0f));

				newTile.setTextureCoordinates(glm::vec2((tileX + tileWidth) / imageWidth, tileY / imageHeight), // top right
											  glm::vec2((tileX + tileWidth) / imageWidth, (tileY + tileHeight) / imageHeight),// bottom right
											  glm::vec2(tileX / imageWidth, (tileY + tileHeight) / imageHeight),// bottom left
											  glm::vec2(tileX / imageWidth, tileY / imageHeight));// top left

				tileX += tileWidth;
				setTile(newTile);
				_id++;
			}
			tileX = 0;
			tileY += tileHeight;
		}

		tinyxml2::XMLElement* pTile = pTileset->FirstChildElement("tile");

		while (pTile) {
			unsigned int id = pTile->IntAttribute("id");
			tinyxml2::XMLElement* pProperty = pTile->FirstChildElement("properties")->FirstChildElement("property");
			std::string propertyName = pProperty->Attribute("value");
			if (propertyName == "false")
				tiles[id].walkability(false);
			else
				tiles[id].walkability(true);

			pTile = pTile->NextSiblingElement("tile");
		}

		// Loading Layer element
		tinyxml2::XMLElement* pLayer = mapNode->FirstChildElement("layer");
		if (pLayer == NULL)
			return false;

		int layerCount = 0;
		while (pLayer) {
			// Loading Data element
			tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData == NULL)
				return false;

			if (layerCount > 0) {
				engine::tile** tileMap;
				tileMap = new engine::tile * [height];

				for (int i = 0; i < height; i++) 
				{
					tileMap[i] = new engine::tile[width];
				}

				tileMapGrid.push_back(tileMap);
			}

			while (pData) {
				std::vector<int> tileGids;
				for (tinyxml2::XMLElement* pTile = pData->FirstChildElement("tile");
					pTile != NULL;
					pTile = pTile->NextSiblingElement("tile"))
				{
					unsigned int gid = std::atoi(pTile->Attribute("gid")); // tile's id is saved
					tileGids.push_back(gid);
				}

				int gid = 0;
				for (int y = 0; y < height; y++) {
					for (int x = 0; x < width; x++) {
						if (tileGids[gid] != 0)
							setMapTileId(layerCount, y, x, tileGids[gid]);
						gid++;
					}
				}

				pData = pData->NextSiblingElement("data");
			}
			layerCount++;
			pLayer = pLayer->NextSiblingElement("layer");
		}

		return true;
	}

	bool tileMap::checkCollision(entity2D& object)
	{
		convertedPosX = object.getPos().x + (width / 2.0f) * tileWidth;
		//convertedPosY = object.getPos().y - (height / 2) * tileHeight;
		convertedPosY = object.getPos().y + (height / 2.0f) * tileHeight;

		int left_tile = convertedPosX / tileWidth;
		int right_tile = (convertedPosX + object.getScale().x) / tileWidth;

		int top_tile = (convertedPosY / tileHeight) * -1;
		int bottom_tile = ((convertedPosY - object.getScale().y) / tileHeight) *-1; // Se resta porque el eje Y crece hacia arriba

		std::cout << std::endl;

		if (left_tile < 0)
			left_tile = 0;

		if (right_tile >= width)
			right_tile = width - 1;

		if (top_tile < 0)
			top_tile = 0;

		if (bottom_tile >= height)
			bottom_tile = height - 1;

		//system("cls");

		//for (int i = 0; i < height; i++)
		//{
		//	for (int j = 0; j < width; j++)
		//	{
		//		if (i <= bottom_tile && i >= top_tile && j >= left_tile && j <= right_tile)
		//		{
		//			color("Red");
		//		}
		//		else
		//		{
		//			color("White");
		//		}
		//		std::cout << "[";
		//		if (j < 10)
		//		{
		//			std::cout << "0";
		//		}
		//
		//		std::cout << j << ",";
		//
		//		if (i < 10)
		//		{
		//			std::cout << "0";
		//		}
		//
		//		std::cout << i << "] ";
		//	}
		//
		//	std::cout << std::endl;
		//}
		//
		//std::cout << "converted X: " << convertedPosX << std::endl;
		//std::cout << "converted Y: " << convertedPosY << std::endl;
		//
		//std::cout << "left: " <<left_tile << std::endl;
		//std::cout << "right: "<<right_tile << std::endl;
		//std::cout << "top: " << top_tile << std::endl;
		//std::cout << "bottom: "<<bottom_tile << std::endl;
		

		for (int i = left_tile; i <= right_tile; i++) 
		{

			for (int j = top_tile; j <= bottom_tile; j++) 
			{

				for (int k = 0; k < tileMapGrid.size(); k++) 
				{
					//std::cout << "caminable " << "[" << k << "]" << "[" << j << "]" << "[" << i << "] : "<< tileMapGrid[k][j][i].isWalkable(); // true == 1  ; false == 0
					//cout << true << endl;
					if (!tileMapGrid[k][j][i].isWalkable()) 
					{
						float overlapX = 0;
						float overlapY = 0;

						engine::collisionType colType = object.checkCollision(tileMapGrid[k][j][i], overlapX, overlapY);

						if (colType != engine::collisionType::none)
						{
							std::cout << "overlapx = " << overlapX << std::endl;
							std::cout << "overlapy = " << overlapY << std::endl;

							object.applyCollisionRestrictions(colType, overlapX, overlapY, false);
							return true;
						}
					}
				}
			}

			//std::cout << std::endl;
		}

		return false;
	}
	int tileMap::getWidth()
	{
		return width;
	}
	int tileMap::getHeight()
	{
		return height;
	}
	std::vector<engine::tile**> tileMap::getTilesGrid()
	{
		return tileMapGrid;
	}
}