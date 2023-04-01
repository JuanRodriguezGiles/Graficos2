#pragma once
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
	};
}
