#include "POVFile.h"
#include "../Polygon/Vertex.h"
#include "../Polygon/TriangleFace.h"
#include "../Polygon/TriangleMesh.h"
#include <fstream>

using namespace Crystal::Polygon;
using namespace Crystal::IO;

bool POVFile::writeScene(const std::string& file, const TriangleMesh& surface)
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

	stream << "mesh {" << std::endl;
	const auto& faces = surface.getFaces();
	for (const auto& f : faces) {
		stream << "triangle {";
			const auto v1 = f->getV1()->getPosition();
			const auto v2 = f->getV2()->getPosition();
			const auto v3 = f->getV3()->getPosition();
			stream << "<" << v1.getX() << "," << v1.getY() << "," << v1.getZ() << ">" << std::endl;
			stream << "<" << v2.getX() << "," << v2.getY() << "," << v2.getZ() << ">" << std::endl;
			stream << "<" << v3.getX() << "," << v3.getY() << "," << v3.getZ() << ">" << std::endl;
		stream << "}" << std::endl;
	}
	//stream << "texture { White_Wood}" << std::endl;
	stream << "texture{ pigment{ color rgb <1,1,1> } } " << std::endl;
	stream << "}" << std::endl;

	return stream.good();
}


bool POVFile::writeInc(const std::string& file, const TriangleMesh& mesh)
{
	std::ofstream stream(file);
	if (!stream.is_open()) {
		return false;
	}

	const auto& faces = mesh.getFaces();
	for (const auto& f : faces) {
		stream << "triangle {";
		const auto v1 = f->getV1()->getPosition();
		const auto v2 = f->getV2()->getPosition();
		const auto v3 = f->getV3()->getPosition();
		stream << "<" << v1.getX() << "," << v1.getY() << "," << v1.getZ() << ">" << std::endl;
		stream << "<" << v2.getX() << "," << v2.getY() << "," << v2.getZ() << ">" << std::endl;
		stream << "<" << v3.getX() << "," << v3.getY() << "," << v3.getZ() << ">" << std::endl;
		stream << "}" << std::endl;
	}

	return stream.good();
}