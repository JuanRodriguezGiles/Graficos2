#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

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
		static node* loadBaseNodeInfo(std::string path);
	};
}
#endif