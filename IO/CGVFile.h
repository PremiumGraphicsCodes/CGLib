#ifndef __CRYSTAL_IO_CGV_FILE_H__
#define __CRYSTAL_IO_CGV_FILE_H__

#include "../Math/Volume3d.h"

#include <string>

namespace Crystal {
	namespace IO {

class CGVFile
{
public:
	bool save(const std::string& filename, const Math::Volume3d<float, float>& volume);

	bool load(const std::string& filename);

	Math::Volume3d<float, float> getVolume() const { return volume; }

private:
	Math::Volume3d<float, float> volume;

};

	}
}
#endif