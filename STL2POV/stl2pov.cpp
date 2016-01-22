#include "../IO/STLFile.h"
#include "../IO/POVFile.h"

using namespace Crystal::Graphics;
using namespace Crystal::IO;

void main(int argc, char** argv)
{
	if (argc < 3) {
		printf("Usage inputfilename outputfilename\n");
		return;
	}

	std::string input = /*"../TestFile/IO/cube-binary.stl";*/ (argv[1]);
	std::string output = /*"../TestFile/IO/cube.pov";*/ (argv[2]);
	STLFileReader reader;
	if (!reader.read(input)) {
		printf("failed");
		return;
	}
	const auto& file = reader.getFile();
	const auto& surface = file.toSurface();

	POVFile pov;
	if (!pov.write(output, surface)) {
		printf("failed");
		return;
	}
}