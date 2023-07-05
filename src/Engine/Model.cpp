#include "Model.h"
#include "textureImporter.h"
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

namespace engine
{
	void Model::Draw(Shader& shader, glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
	{

		unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		unsigned int projectionLoc = glGetUniformLocation(shader.ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);
	}
	void Model::loadModel(string path)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));

		baseNode = new node();
		processNode(scene->mRootNode, scene, baseNode);
		baseNode->setParent(NULL);
	}
	void Model::processNode(aiNode* node, const aiScene* scene, engine::node* myNode)
	{
		// process all the node's meshes (if any)
		vector<Mesh> nodeMeshes;

		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			Mesh newMesh = processMesh(mesh, scene);
			meshes.push_back(newMesh);
			nodeMeshes.push_back(newMesh);
		}

		myNode->setMeshes(nodeMeshes);
		myNode->setName(node->mName.C_Str());

		glm::mat4 mat;

		mat[0].x = node->mTransformation.a1; mat[1].x = node->mTransformation.b1; mat[2].x = node->mTransformation.c1; mat[3].x = node->mTransformation.d1;
		mat[0].y = node->mTransformation.a2; mat[1].y = node->mTransformation.b2; mat[2].y = node->mTransformation.c2; mat[3].y = node->mTransformation.d2;
		mat[0].z = node->mTransformation.a3; mat[1].z = node->mTransformation.b3; mat[2].z = node->mTransformation.c3; mat[3].z = node->mTransformation.d3;
		mat[0].w = node->mTransformation.a4; mat[1].w = node->mTransformation.b4; mat[2].w = node->mTransformation.c4; mat[3].w = node->mTransformation.d4;

		//myNode->setLocalModel(mat);

		// then do the same for each of its children
		vector<engine::node*> childrenNodes;
		childrenNodes.clear();

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			engine::node* myNodeChild = new engine::node();
			processNode(node->mChildren[i], scene, myNodeChild);

			myNodeChild->setParent(myNode);
			myNodeChild->UseLocalMatrix();
			childrenNodes.push_back(myNodeChild);
		}

		if (childrenNodes.size() > 0)
			myNode->setChildren(childrenNodes);
	}
	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			// process vertex positions, normals and texture coordinates
			Vertex vertex;

			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;

			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		// process indices


		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		// process material
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			vector<Texture> diffuseMaps = loadMaterialTextures(material,
				aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			vector<Texture> specularMaps = loadMaterialTextures(material,
				aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(vertices, indices, textures);
	}
	vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (unsigned int j = 0; j < textures_loaded.size(); j++)
			{
				if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{   // if texture hasn't been loaded already, load it
				Texture texture;
				texture.id = textureImporter::TextureFromFile(str.C_Str(), directory);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				textures_loaded.push_back(texture); // add to loaded textures
			}
		}
		return textures;
	}
}