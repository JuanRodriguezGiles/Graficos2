#pragma once
#include "Model.h"
#include "renderer.h"
#include <list>

namespace engine
{

	class ENGINE_API modelImporter
	{
	public:
		modelImporter();
		~modelImporter();
		static vector<Mesh> loadModel(std::string path);
	};
}