#include "CGVFile.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

bool CGVFile::save(const std::string& filename, const Volume3d<float, float>& volume)
{
	const auto& grid = volume.getGrid();
	const auto& space = volume.getSpace();

	std::ofstream stream;
	stream.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);

	if (!stream.is_open()) {
		return false;
	}

	const std::string str("CGStudio File Format Version = 0.3.0");
	stream.write(str.data(), 50);

	const auto startx = space.getStart().getX();
	stream.write((char*)&startx, sizeof(startx));
	const auto starty = space.getStart().getY();
	stream.write((char*)&starty, sizeof(starty));
	const auto startz = space.getStart().getY();
	stream.write((char*)&startz, sizeof(startz));

	const auto lengthx = space.getLengths().getX();
	stream.write((char*)&lengthx, sizeof(lengthx));
	const auto lengthy = space.getLengths().getY();
	stream.write((char*)&lengthy, sizeof(lengthy));
	const auto lengthz = space.getLengths().getZ();
	stream.write((char*)&lengthz, sizeof(lengthz));

	const auto resx = grid.getSizeX();
	stream.write((char*)&resx, sizeof(resx));
	const auto resy = grid.getSizeY();
	stream.write((char*)&resy, sizeof(resy));
	const auto resz = grid.getSizeZ();
	stream.write((char*)&resz, sizeof(resz));

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

	char str[50];
	stream.read(str, 50);

	const float startx = 0.0f;
	stream.read((char*)&startx, sizeof(startx));
	const float starty = 0.0f;
	stream.read((char*)&starty, sizeof(starty));
	const float startz = 0.0f;
	stream.read((char*)&startz, sizeof(startz));

	float lengthx = 0.0f;
	stream.read((char*)&lengthx, sizeof(lengthx));
	float lengthy = 0.0f;
	stream.read((char*)&lengthy, sizeof(lengthy));
	float lengthz = 0.0f;
	stream.read((char*)&lengthz, sizeof(lengthz));

	int resx = 0;
	stream.read((char*)&resx, sizeof(resx));

	int resy = 0;
	stream.read((char*)&resy, sizeof(resy));

	int resz = 0;
	stream.read((char*)&resz, sizeof(resz));

	auto space = Space3d<float>(Vector3d<float>(startx, starty, startz), Vector3d<float>(lengthx, lengthy, lengthz));
	auto grid = Grid3d<float>(resx, resy, resz);

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
