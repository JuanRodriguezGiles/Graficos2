#include "modelImporter.h"

namespace engine
{
	modelImporter::modelImporter()
	{
	}

	modelImporter::~modelImporter()
	{
	}

	node* modelImporter::chargeBaseNodeInfo(std::string path)
	{
		Model* newModel = new engine::Model(path);

		return newModel->GetBaseNode();
	}
}