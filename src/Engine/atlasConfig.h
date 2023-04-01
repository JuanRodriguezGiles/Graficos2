#pragma once
namespace engine
{
	class atlasCutConfig
	{
	public:
		void CutByCount(int columns, int rows, int offsetX, int offsetY, int framesAmount)
		{
			this->columns = columns;
			this->rows = rows;
			this->offsetX = offsetX;
			this->offsetY = offsetY;
			this->framesAmount = framesAmount;
			useSize = false;
		}
		void CutBySize(int spriteWidth, int spriteHeight, int offsetX, int offsetY, int framesAmount)
		{
			this->spriteWidth = spriteWidth;
			this->spriteHeight = spriteHeight;
			this->offsetX = offsetX;
			this->offsetY = offsetY;
			this->framesAmount = framesAmount;
			useSize = true;
		}
	private:
		int columns = 1;
		int rows = 1;
		int offsetX = 0;
		int offsetY = 0;
		int framesAmount = 1;
		bool useSize = false;
		int spriteWidth = 0;
		int spriteHeight = 0;
		friend class animation;
		friend class sprite;
	};
}