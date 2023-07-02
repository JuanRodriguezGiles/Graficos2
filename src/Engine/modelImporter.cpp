#include "modelImporter.h"

namespace engine
{
	modelImporter::modelImporter()
	{
	}

	modelImporter::~modelImporter()
	{
	}

	vector<Mesh> modelImporter::loadModel(std::string path)
	{
		Model* newModel = new engine::Model(path);

		return newModel->GetMeshes();
	}
}