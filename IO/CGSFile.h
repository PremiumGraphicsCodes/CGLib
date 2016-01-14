#ifndef __CRYSTAL_IO_CGS_FILE_H__
#define __CRYSTAL_IO_CGS_FILE_H__

#include "TinyXML.h"

#include "../Math/Volume3d.h"

#include <string>
#include <memory>
#include <vector>

namespace Crystal {
	namespace IO {

class CGSFile
{
public:
	bool save(const std::string& filename, const Math::Grid3d<float>& volume);

	bool load(const std::string& filename);

	Math::Grid3d<float> getGrid() const { return grid; }

private:
	Math::Grid3d<float> grid;
};
	}
}
#endif