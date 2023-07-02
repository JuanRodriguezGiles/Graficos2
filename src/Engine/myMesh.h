#pragma once
#include "exports.h"
#include "GLM/glm.hpp"
#include <vector>
#include <string>
#include "renderer.h"

using namespace std;

namespace engine
{
	class ENGINE_API myMesh
	{
	public:
		vector<myVertex>       vertices;
		vector<unsigned int> indices;
		vector<myTexture>      textures;
		unsigned int VAO, VBO, EBO;
		myMesh(vector<myVertex> vertices, vector<unsigned int> indices, vector<myTexture> textures, unsigned int VAO, unsigned int VBO, unsigned int EBO);
		void draw(renderer* render);
	private:
	};
}