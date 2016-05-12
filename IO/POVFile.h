#ifndef __CRYSTAL_IO_POV_FILE_H__
#define __CRYSTAL_IO_POV_FILE_H__

#include <string>
#include <list>

namespace Crystal {
	namespace Polygon {
		class PolygonMesh;
	}
	namespace IO {

class POVFile
{
public:
	bool writeScene(const std::string& file, const std::list< Polygon::PolygonMesh *>& meshes);

	bool writeInc(const std::string& file, const std::list< Polygon::PolygonMesh* >& meshes);

private:

	bool writeMesh(std::ostream& stream, const Polygon::PolygonMesh& mesh);

};
	}
}

#endif