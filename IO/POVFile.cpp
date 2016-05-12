#include "POVFile.h"
#include "../Polygon/Vertex.h"
#include "../Polygon/Face.h"
#include "../Polygon/PolygonObject.h"
#include <fstream>

using namespace Crystal::Polygon;
using namespace Crystal::IO;

bool POVFile::writeScene(const std::string& file, const std::list< PolygonMesh *>& meshes)
{
	std::ofstream stream(file);
	if (!stream.is_open()) {
		return false;
	}

	stream << "#include \"colors.inc\"" << std::endl;
	stream << "#include \"textures.inc\"" << std::endl;

	stream << "camera {" << std::endl;
	stream << "location <1,1,-2>" << std::endl;
	stream << "look_at <0,0,0>" << std::endl;
	stream << "}" << std::endl;

	stream << "light_source {" << std::endl;
	stream << "<10,10,-10>" << std::endl;
	stream << "color rgb <1,1,1>" << std::endl;
	stream << "}" << std::endl;

	stream << "plane {" << std::endl;
	stream << "<0,1,0>,-1" << std::endl;
	stream << "pigment {color Pink}" << std::endl;
	stream << "}" << std::endl;

	for (const auto& m : meshes) {
		writeMesh(stream, *m);
	}
	return stream.good();
}


bool POVFile::writeInc(const std::string& file, const std::list< PolygonMesh *>& meshes)
{
	std::ofstream stream(file);
	if (!stream.is_open()) {
		return false;
	}

	for (const auto& m : meshes) {
		writeMesh(stream, *m);
	}
	return stream.good();
}

bool POVFile::writeMesh(std::ostream& stream, const PolygonMesh& mesh)
{
	const auto& vertices = mesh.getVertices();

	stream << "mesh2 {" << std::endl;

	{
		stream << "vertex_vectors {" << std::endl;
		stream << vertices.size() << "," << std::endl;
		for (const auto& v : vertices) {
			const auto x = v->getPosition().getX();
			const auto y = v->getPosition().getY();
			const auto z = v->getPosition().getZ();
			stream << "<" << x << "," << y << "," << z << ">" << std::endl;
		}
		stream << "}" << std::endl;
	}

	{
		const auto& faces = mesh.getFaces();
		stream << "face_indices {" << std::endl;
		stream << faces.size() << std::endl;
		for (const auto& f : faces) {
			const auto i1 = f->getV1()->getId();
			const auto i2 = f->getV2()->getId();
			const auto i3 = f->getV3()->getId();
			stream << "<" << i1 << "," << i2 << "," << i3 << ">" << std::endl;
		}
		stream << "}" << std::endl;
		stream << "pigment {rgb 1}" << std::endl;
	}
	stream << "}" << std::endl;

	return stream.good();
}
