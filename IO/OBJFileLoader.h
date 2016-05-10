#ifndef __CRYSTAL_IO_OBJ_FILE_LOADER_H__
#define __CRYSTAL_IO_OBJ_FILE_LOADER_H__

#include "OBJFile.h"
#include "MTLFile.h"
#include "../Graphics/VisualPolygon.h"

namespace Crystal {
	namespace IO {

class OBJFileLoader
{
public:
	bool load(const File& file);

private:
	OBJFile objFile;
	std::vector<MTLFile> mtlFiles;
	Graphics::VisualPolygon visualPolygon;
};
	}
}

#endif