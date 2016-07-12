#include "stdafx.h"
#include "STLFile.h"

#include "Helper.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::IO;

#include <string>
#include <cassert>
#include "../Core/Face.h"
#include "../Core/Vertex.h"


void STLFile::add(const PolygonMesh& mesh)
{
	const auto faces = mesh.getFaces();
	for (auto f : faces) {
		STLCell cell;
		cell.addPosition(f->getV1()->getPosition());
		cell.addPosition(f->getV2()->getPosition());
		cell.addPosition(f->getV3()->getPosition());
		cell.setNormal(f->getNormal());
		cells.push_back(cell);
	}
}

PolygonMesh* STLFile::toPolygonObject() const
{
	PolygonMesh* polygon = new PolygonMesh();
	for (const auto& c : cells) {
		const auto& pos = c.getPositions();
		const auto& normal = c.getNormal();
		const auto v1 = polygon->createVertex(pos[0], normal);
		const auto v2 = polygon->createVertex(pos[1], normal);
		const auto v3 = polygon->createVertex(pos[2], normal);
		polygon->createFace(v1, v2, v3);
	}
	return polygon;
}



bool STLFile::read(const std::string& filename) {
	std::ifstream stream(filename);
	return read(stream);
}

bool STLFile::read(std::istream& stream)
{
	std::string str0, str1, str2;
	stream >> str0;
	stream >> str1;
	stream >> str2;
	stream.seekg(0, std::ios_base::beg);

	if (str0 == "solid" && str2 == "facet") {
		return readASCII(stream);
	}
	else {
		return readBinary(stream);
	}

}


bool STLFile::readASCII(std::istream& stream)
{
	std::string str = Helper::read<std::string>(stream);

	assert(str == "solid");

	std::getline(stream, str);

	this->title = str;

	str = Helper::read<std::string>(stream);
	while (str != "endsolid") {
		assert(str == "facet");
		str = Helper::read<std::string>(stream);
		assert(str == "normal");

		STLCell cell;
		const Vector3d<float>& normal = Helper::readVector(stream);
		cell.setNormal(normal);

		stream >> str;
		assert(str == "outer");

		stream >> str;
		assert(str == "loop");

		for (int i = 0; i < 3; ++i) {
			stream >> str;
			assert(str == "vertex");

			const Vector3d<float>& position = Helper::readVector(stream);
			cell.addPosition(position);
		}
		cells.push_back(cell);

		str = Helper::read<std::string>(stream);
		assert(str == "endloop");

		str = Helper::read<std::string>(stream);
		assert(str == "endfacet");

		str = Helper::read<std::string>(stream);
	}

	return stream.good();
}


bool STLFile::readBinary(std::istream& stream) {
	char head[80];
	stream.read(head, 80);

	unsigned int howMany;
	stream.read((char *)&howMany, sizeof(unsigned int));

	for (size_t i = 0; i < howMany; ++i) {
		float normal[3];
		stream.read((char *)&normal, sizeof(float) * 3);
		float pos0[3];
		stream.read((char *)&pos0, sizeof(float) * 3);
		float pos1[3];
		stream.read((char *)&pos1, sizeof(float) * 3);
		float pos2[3];
		stream.read((char *)&pos2, sizeof(float) * 3);
		char padding[2];
		stream.read((char *)padding, sizeof(char) * 2);
		
		if (!stream.good()) {
			assert(false);
		}

		STLCell cell;
		cell.setNormal(Vector3d<float>(normal[0], normal[1], normal[2]));
		cell.addPosition(Vector3d<float>(pos0[0], pos0[1], pos0[2]));
		cell.addPosition(Vector3d<float>(pos1[0], pos1[1], pos1[2]));
		cell.addPosition(Vector3d<float>(pos2[0], pos2[1], pos2[2]));
		//faces.push_back( f );
		cells.push_back(cell);
	}
	return stream.good();
}



bool STLFile::writeASCII(const std::string& filename)
{
	std::ofstream stream;
	stream.open(filename);
	if (!stream.is_open()) {
		return false;
	}

	return writeASCII(stream);
}

bool STLFile::writeASCII(std::ostream& stream)
{
	stream << "solid" << " " << title << std::endl;

	for (const STLCell& cell : cells) {
		stream << "facet" << " ";
		const Vector3d<float>& normal = cell.getNormal();
		stream << "normal" << " " << normal.getX() << " " << normal.getY() << " " << normal.getZ() << std::endl;
		stream << "outer loop" << std::endl;
		const std::vector< Vector3d<float> >& positions = cell.getPositions();
		for (const Vector3d<float>& pos : positions) {
			stream << "vertex" << " " << pos.getX() << " " << pos.getY() << " " << pos.getZ() << std::endl;
		}
		stream << "endloop" << std::endl;
		stream << "endfacet" << std::endl;
	}
	stream << "endsolid" << std::endl;

	return stream.good();
}



bool STLFile::writeBinary(const std::string& filename)
{
	std::ofstream stream;
	stream.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!stream.is_open()) {
		return false;
	}
	return writeBinary(stream);
}


bool STLFile::writeBinary(std::ostream& stream)
{
	const char* head = title.c_str();
	stream.write(head, 80);

	const auto howMany = cells.size();
	stream.write((char *)&howMany, sizeof(unsigned int));

	for (const STLCell& cell : cells) {
		const std::vector<float>& normal = cell.getNormal().toArray();
		stream.write((char *)&(normal.front()), sizeof(float) * 3);
		for (const Vector3d<float>& pos : cell.getPositions()) {
			const std::vector<float>& p = pos.toArray();
			stream.write((char *)&(p.front()), sizeof(float) * 3);
		}
		char padding[2];
		padding[0] = '0';
		padding[1] = '0';
		stream.write(padding, sizeof(char) * 2);
	}

	return stream.good();
}
