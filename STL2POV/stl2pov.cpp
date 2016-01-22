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
	
	std::string input = argv[1];//"C:/Users/PremiumGraphics/Desktop/POVTest/cubex.stl"; (argv[1]);
	std::string output = argv[2];//"C:/Users/PremiumGraphics/Desktop/POVTest/cubex.pov";// (argv[2]);
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