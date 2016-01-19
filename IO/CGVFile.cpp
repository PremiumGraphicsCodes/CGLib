#include "CGVFile.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

bool CGVFile::save(const std::string& filename, const Volume3d<float, float>& volume)
{
	std::ofstream stream;
	stream.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);

	if (!stream.is_open()) {
		return false;
	}

	const auto& grid = volume.getGrid();
	const auto& space = volume.getSpace();

	stream << "CGStudioFileFormatVersion 0 3 0" << std::endl;
	stream
		<< "SpaceMin" << " "
		<< space.getStart().getX() << " "
		<< space.getStart().getY() << " " 
		<< space.getStart().getZ()
		<< std::endl;
	stream
		<< "SpaceLength" << " "
		<< space.getLengths().getX() << " "
		<< space.getLengths().getY() << " "
		<< space.getLengths().getZ()
		<< std::endl;
	stream
		<< "SpaceResolution" << " "
		<< grid.getSizeX() << " "
		<< grid.getSizeY() << " "
		<< grid.getSizeZ()
		<< std::endl;

	for (int i = 0; i< grid.getSizeX(); i++) {
		for (int j = 0; j < grid.getSizeY(); ++j) {
			for (int k = 0; k < grid.getSizeZ(); ++k) {
				auto v = grid.get(i, j, k);
				stream.write((char *)&v, sizeof(v));
			}
		}
	}

	stream.close();

	return true;
}

bool CGVFile::load(const std::string& filename)
{
	std::ifstream stream;
	stream.open(filename, std::ios::in | std::ios::binary);

	if (!stream.is_open()) {
		return false;
	}

	std::string str;
	stream >> str;

	assert(str == "CGStudioFileFormatVersion");

	int majorversion = 0;
	stream >> majorversion;
	int minorversion = 0;
	stream >> minorversion;
	int patchversion = 0;
	stream >> patchversion;

	stream >> str;
	assert(str == "SpaceMin");

	float minx = 0;
	stream >> minx;

	float miny = 0;
	stream >> miny;

	float minz = 0;
	stream >> minz;

	stream >> str;
	assert(str == "SpaceLength");

	float lengthx = 0;
	stream >> lengthx;

	float lengthy = 0;
	stream >> lengthy;

	float lengthz = 0;
	stream >> lengthz;

	stream >> str;
	assert(str == "SpaceResolution");

	int resx = 0;
	stream >> resx;

	int resy = 0;
	stream >> resy;

	int resz = 0;
	stream >> resz;

	stream >> str;

	auto grid = Grid3d<float>(resx, resy, resz);
	auto space = Space3d<float>(Vector3d<float>(minx, miny, minz), Vector3d<float>(lengthx, lengthy, lengthz));

	for (int i = 0; i< resx; i++) {
		for (int j = 0; j < resy; ++j) {
			for (int k = 0; k < resz; ++k) {
				auto v = 0.0f;
				stream.read((char *)&v, sizeof(v));
				grid.set(i, j, k, v);
			}
		}
	}

	this->volume = Volume3d<float, float>(space, grid);

	return true;
}
