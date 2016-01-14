#include "CGSFile.h"

#include <iostream>
#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

bool CGSFile::save(const std::string& filename, const Grid3d<float>& grid)
{
	std::ofstream stream;
	stream.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);

	if (!stream.is_open()) {
		return false;
	}

	const std::string str("CGStudio File Format Version = 0.2.0");
	stream.write(str.data(), 50);

	const auto resx = grid.getSizeX();
	stream.write((char*)&resx, sizeof(resx));
	const auto resy = grid.getSizeY();
	stream.write((char*)&resy, sizeof(resy));
	const auto resz = grid.getSizeZ();
	stream.write((char*)&resz, sizeof(resz));

	for (int i = 0; i< grid.getSizeX(); i++) {
		for (int j = 0; j < grid.getSizeY(); ++j) {
			for (int k = 0; k < grid.getSizeZ(); ++k) {
				auto v = grid.get(i,j,k);
				stream.write((char *)&v, sizeof(v));
			}
		}
	}

	stream.close();

	return true;
}

bool CGSFile::load(const std::string& filename)
{
	std::ifstream stream;
	stream.open(filename, std::ios::in | std::ios::binary);

	if (!stream.is_open()) {
		return false;
	}

	char str[50];
	stream.read(str, 50);

	int resx = 0;
	stream.read((char*)&resx, sizeof(resx));

	int resy = 0;
	stream.read((char*)&resy, sizeof(resy));

	int resz = 0;
	stream.read((char*)&resz, sizeof(resz));

	grid = Grid3d<float>(resx, resy, resz);

	for (int i = 0; i< resx; i++) {
		for (int j = 0; j < resy; ++j) {
			for (int k = 0; k < resz; ++k) {
				auto v = 0.0f;
				stream.read((char *)&v, sizeof(v));
				grid.set(i,j,k,v);
			}
		}
	}

	//stream.read

	return true;
}
