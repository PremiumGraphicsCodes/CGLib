#include "VMDFile.h"

#include <fstream>

using namespace Crystal::IO;

VMDHeader::VMDHeader():
	header("Vocaloid Motion Data 0002")
{

}


bool VMDHeader::read(std::istream& stream)
{
	stream.read(header, sizeof(header));
	stream.read(modelName, sizeof(modelName));
	return stream.good();
}

bool VMDHeader::write(std::ostream& stream)
{
	stream.write(header, sizeof(header));
	stream.write(modelName, sizeof(modelName));
	return stream.good();
}

bool VMDMotion::read(std::istream& stream)
{
	stream.read(boneName, sizeof(boneName));
	stream.read((char*)frameNumber, sizeof(frameNumber));
	stream.read((char*)location, sizeof(location));
	stream.read((char*)rotation, sizeof(rotation));
	stream.read((char*)interpolation, sizeof(interpolation));
	return stream.good();
}

bool VMDFile::read(const std::string& filename)
{
	std::ifstream stream(filename, std::ios::in | std::ios::binary | std::ios::trunc);
	if (!stream.is_open()) {
		return false;
	}
	header.read(stream);
	DWORD motionNumber = 0;
	stream.read((char*)motionNumber, sizeof(motionNumber));
	for (int i = 0; i < motionNumber; ++i) {
		VMDMotion motion;
		motion.read(stream);
		motions.emplace_back(motion);
	}
	return stream.good();
}

bool VMDFile::write(const std::string& filename)
{
	return false;
}
