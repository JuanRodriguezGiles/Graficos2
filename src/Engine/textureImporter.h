#pragma once
#include <string>
#include <iostream>

namespace engine
{
	struct textureData
	{
		unsigned int ID;
		float width;
		float height;
	};

	class textureImporter
	{
	public:
		static textureData loadTexture(const char* filepath, bool invertVertical);
		static unsigned int TextureFromFile(const char* path, const std::string& directory);
	};
}
