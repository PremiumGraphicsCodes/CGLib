#include "OBJFileLoader.h"


using namespace Crystal::IO;

bool OBJFileLoader::load(const File& file)
{
	objFile.read(file);
	auto libs = objFile.getMTLLibs();
	for (auto lib : libs) {
		std::string mtlFileName = file.getFolerPath() + lib;
		MTLFile mtlFile;
		mtlFile.read(mtlFileName);
		mtlFiles.push_back(mtlFile);
	}
	return true;
}