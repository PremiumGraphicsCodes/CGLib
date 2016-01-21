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
 		for (const auto& e : f.getEdges()) {
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

	return true;
}
