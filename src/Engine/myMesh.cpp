#include "myMesh.h"

namespace engine
{
	myMesh::myMesh(vector<myVertex> vertices, vector<unsigned int> indices, vector<myTexture> textures, unsigned int VAO, unsigned int VBO, unsigned int EBO)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		this->VAO = VAO;
		this->VBO = VBO;
		this->EBO = EBO;
	}
}