#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "exports.h"
#include "node.h"

using namespace std;

namespace engine
{
    class ENGINE_API Model
    {
    public:
        Model(string path)
        {
            loadModel(path);
        }
        void Draw(Shader& shader, glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
        vector<Mesh> GetMeshes() { return meshes; };
        node* GetBaseNode() { return baseNode; };
    private:
        // model data
        vector<Texture> textures_loaded;
        vector<Mesh> meshes;
        string directory;
        node* baseNode;

        void loadModel(string path);
        void processNode(aiNode* node, const aiScene* scene, engine::node* myNode);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
            string typeName);
    };
}

#endif