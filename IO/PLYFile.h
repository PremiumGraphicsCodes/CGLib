#ifndef __CRYSTAL_IO_PLY_FILE_H__
#define __CRYSTAL_IO_PLY_FILE_H__

#include "../Math/Vector3d.h"

#include <string>

namespace Crystal {
	namespace IO {

class PLYFile final
{
public:
	bool read(const std::string& filename);

	bool read(std::istream& stream);

	bool write(const std::string& filename, const std::vector<Math::Vector3d<float>>& points);

	bool write(std::ostream& stream, const std::vector<Math::Vector3d<float>>& points);
private:
};
	}
}

#endif