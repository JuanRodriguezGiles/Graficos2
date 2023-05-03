#pragma once
#include "exports.h"
#include "entity2D.h"

namespace engine
{
	enum SHAPE { TRIANGLE, QUAD, CUBE };

	class ENGINE_API shape : public entity2D
	{
	public:
		shape(renderer* render, SHAPE shape, bool affectedByLight);
		~shape();
		void draw() override;
	private:
		//void setShader();
		unsigned int bufferPosUVs = 0;
	};
}