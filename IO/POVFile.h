#ifndef __CRYSTAL_IO_POV_FILE_H__
#define __CRYSTAL_IO_POV_FILE_H__

#include <string>
#include <list>

namespace Crystal {
	namespace Polygon {
		class PolygonObject;
	}
	namespace IO {

class POVFile
{
public:
	bool writeScene(const std::string& file, const std::list< Polygon::PolygonObject *>& meshes);

	bool writeInc(const std::string& file, const std::list< Polygon::PolygonObject* >& meshes);

private:

	bool writeMesh(std::ostream& stream, const Polygon::PolygonObject& mesh);

};
	}
}

#endif