#include "POVFile.h"
#include <fstream>

using namespace Crystal::Graphics;
using namespace Crystal::IO;

bool POVFile::write(const std::string& file, const Surface<float>& surface)
{
	std::ofstream stream(file);
	if (!stream.is_open()) {
		return false;
	}

	stream << "mesh {" << std::endl;
	const auto& faces = surface.getFaces();
	for (const auto& f : faces) {
		stream << "triangle {";
		const auto& edges = f.getEdges();
 		for (const auto& e : edges) {
			const auto& v = e.getStartPosition();
			const auto x = v.getX();
			const auto y = v.getY();
			const auto z = v.getZ();
			stream << "<" << x << "," << y << "," << z << ">" << std::endl;
		}
		stream << "}" << std::endl;
	}
	//stream << "texture { White_Wood}" << std::endl;
	stream << "texture{ pigment{ color rgb <1,1,1> } } " << std::endl;
	stream << "}" << std::endl;

	return stream.good();
}
