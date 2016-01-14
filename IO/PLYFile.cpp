#include "PLYFile.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

bool PLYFile::read(const std::string& filename)
{
	return false;
}

bool PLYFile::read(std::istream& stream)
{
	return false;
}

bool PLYFile::write(const std::string& filename, const Vector3dVector<float>& points)
{
	return false;
}

bool PLYFile::write(std::ostream& stream, const Vector3dVector<float>& points)
{
	stream << "ply" << std::endl;
	stream << "format ascii 1.0" << std::endl;
	stream << "comment" << " " << std::endl;
	stream << "elememt" << " vertex " << points.size() << std::endl;
	stream << "property" << " double " << "x" << std::endl;
	stream << "property" << " double " << "y" << std::endl;
	stream << "property" << " double " << "z" << std::endl;
	stream << "end_header" << std::endl;
	for (const auto& p : points) {
		stream << p.getX() << " " << p.getY() << " " << p.getZ() << std::endl;
	}
	return true;
}
