#include "OBJFileLoader.h"


using namespace Crystal::IO;

bool OBJFileLoader::load(const File& file)
{
	objFile.read(file);
	auto libs = objFile.getMTLLibs();
	for (auto lib : libs) {
		std::string mtlFileName = file.getFolerPath() + "/" + lib.second;
		MTLFile mtlFile;
		mtlFile.read(mtlFileName);
	}
	return true;
}