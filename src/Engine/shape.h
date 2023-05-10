#pragma once
#include "exports.h"
#include "entity2D.h"
#include "renderer.h"

namespace engine
{
	enum class SHAPE { TRIANGLE, QUAD, CUBE };

	class ENGINE_API shape : public entity2D
	{
	public:
		shape(renderer* render, SHAPE shape, MATERIAL material);
		~shape();
		void draw() override;
	private:
		unsigned int bufferPosUVs = 0;
		MATERIAL material;
		textureData* texture;
	};
}