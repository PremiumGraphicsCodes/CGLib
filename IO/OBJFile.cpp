#define _CRT_SECURE_NO_DEPRECATE

#include "OBJFile.h"

#include <fstream>
#include <cassert>
#include <vector>

#include "../Math/Vector3d.h"
#include "../Polygon/Vertex.h"
#include "../Polygon/Face.h"

#include "Helper.h"

#include <string>
#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Polygon;
using namespace Crystal::IO;

bool OBJGroup::read(std::istream& stream, bool hasTitle)
{
	std::string header;
	std::string str;

	if (hasTitle) {
		header = Helper::read< std::string >(stream);
		//assert(header == 'g');
		std::getline(stream, str);
		header = Helper::read< std::string >(stream);

	}

	while (!stream.eof()) {

		if (header == "#") {
			std::getline(stream, str);
			//header = read< std::string >();
		}
		else if (header == "f") {
			std::getline(stream, str);
			faces.push_back(readFaces(str));
		}
		else if (header == "usemtl") {
			std::getline(stream, str);
			//OBJMaterial material(str);
			const std::string name = str;
			materials.push_back(name);
			std::string useMtlName = name;
		}
		else if (header == "g") {
			return true;
		}
		header = Helper::read< std::string >(stream);

	}
	return true;
}

OBJFace OBJGroup::readFaces(const std::string& str)
{
	std::vector< std::string >& strs = Helper::split(str, ' ');

	OBJVertex vertex;
	//assert(strs.front() == "f");
	std::vector<OBJVertex> vertices;
	for (unsigned int i = 0; i < strs.size(); ++i) {
		if (strs[i].empty()) {
			continue;
		}
		std::string::size_type pos( strs[i].find("//"));
		if (pos != std::string::npos) {
			strs[i].replace( pos, 2, "/ /");
		}

		std::vector<std::string>& splitted = Helper::split(strs[i], '/');
		vertex.positionIndex = std::stoi(splitted[0]);
		//vertexIndices.push_back(index);
		if (splitted.size() >= 2 && splitted[1] != " " ) {
			vertex.texIndex = std::stoi(splitted[1]);
		}
		if (splitted.size() >= 3) {
			vertex.normalIndex = std::stoi(splitted[2]);
		}
		vertices.push_back(vertex);
	}
	return OBJFace( vertices );
}

void OBJFile::add(const PolygonObject& polygon)
{
	const auto& vertices = polygon.getVertices();
	for (const auto& v : vertices) {
		positions.push_back(v->getPosition());
		normals.push_back(v->getNormal());
		texCoords.push_back(v->getTexCoord());
	}
	const auto& faces = polygon.getFaces();
	std::vector<OBJFace> objFaces;
	for (const auto& f : faces) {
		std::vector<OBJVertex> vs;
		const auto index1 = f->getV1()->getId();
		const auto index2 = f->getV2()->getId();
		const auto index3 = f->getV3()->getId();
		OBJVertex v1(index1, index1, index1);
		OBJVertex v2(index2, index2, index2);
		OBJVertex v3(index3, index3, index3);
		OBJFace face({ v1, v2, v3 });
		objFaces.push_back(face);
	}
	OBJGroup group;
	group.setFaces(objFaces);
	groups.push_back(group);
}

std::vector<PolygonObject*> OBJFile::toPolygonObjects()
{
	std::vector<PolygonObject*> polygons;
	for (auto& g : groups) {
		PolygonObject* polygon = new PolygonObject();
		for (auto f : g.getFaces()) {
			auto vs = f.getVertices();
			std::vector<Vertex*> vv;
			for (const auto v : vs) {
				const auto& position = positions[v.positionIndex - 1];
				const auto& normal = normals[v.normalIndex - 1];
				const auto& texCoord = texCoords[v.texIndex - 1];
				auto v = polygon->createVertex(position, normal, texCoord);
				vv.push_back(v);
			}
			polygon->createFaces(vv);
		}
		polygons.push_back(polygon);
	}
	return polygons;
}

bool OBJFile::read(const File& file)
{
	const std::string fullPathName = file.getFullPath();// path + "/" + filename;

	std::ifstream stream;
	stream.open(fullPathName.c_str());

	assert(stream.is_open());

	return read(stream);
}


bool OBJFile::read(std::istream& stream)
{
	std::string str;

	std::string header;

	while (!stream.eof()) {

		if (header == "#") {
			std::getline(stream, str);
			//header = read< std::string >();
		}
		else if (header == "v") {
			std::getline(stream, str);
			positions.push_back(readVertices(str));
		}
		else if (header == "vt") {
			std::getline(stream, str);
			texCoords.push_back(readVector3d(str));
		}
		else if (header == "vn" || header == "-vn") {
			std::getline(stream, str);
			normals.push_back(readVector3d(str));
		}
		header = Helper::read< std::string >(stream);
	}

	stream.clear();
	stream.seekg(0, std::ios::beg);

	if (containsGroup(stream)) {
		//stream.clear();
		//stream.seekg(0, std::ios::beg);
		while(!stream.eof()) {
			OBJGroup group;
			group.read(stream, true);
			groups.push_back(group);
		}
	}
	else {
		stream.clear();
		stream.seekg(0, std::ios::beg);
		OBJGroup group;
		group.read(stream, false);
		groups.push_back(group);
	}
	return stream.good();
}


Vector3d<float> OBJFile::readVertices(const std::string& str)
{
	const std::vector< std::string >& strs = Helper::split(str, ' ');
	//assert(strs.front() == "v");

	const float x = std::stof(strs[0].c_str());
	const float y = std::stof(strs[1].c_str());
	const float z = std::stof(strs[2].c_str());
	if (strs.size() == 4) {
		const float w = ::std::stof(strs[3].c_str());
		return Vector3d<float>(x, y, z);
	}
	else {
		return Vector3d<float>(x, y, z);
	}
}

Vector3d<float> OBJFile::readVector3d(const std::string& str)
{
	const std::vector< std::string >& strs = Helper::split(str, ' ');
	//assert(strs.front() == "vt");
	const float u = ::std::stof(strs[0]);
	const float v = ::std::stof(strs[1]);
	if (strs.size() == 3) {
		const float w = std::stof(strs[2]);
		return Vector3d<float>(u, v, w);
	}
	else {
		return Vector3d<float>(u, v, 0.0f);
	}
}

bool OBJFile::write(const std::string& path, const std::string& filename, const PolygonObject& mesh)
{
	const std::string fullPathName = path + "/" + filename;
	std::ofstream stream(fullPathName.c_str());

	if (!stream.is_open()) {
		return false;
	}
	return write(stream, mesh);
}

bool OBJFile::write(std::ostream& stream, const PolygonObject& mesh)
{
	const auto& positions = mesh.getPositions();
	const auto& normals = mesh.getNormals();
	const auto& faces = mesh.getFaces();

	//for (const auto& v : positions) {
	for (unsigned int i = 0; i < positions.size(); ++i) {
		const auto pos = positions[i];
		char s[256];
		sprintf(s, "v %.4lf %.4lf %.4lf", pos.getX(), pos.getY(), pos.getZ());
		stream << s << std::endl;
	}

	for (unsigned int i = 0; i < normals.size(); ++i ){
		const auto vn = normals[i];
		char s[256];
		sprintf(s, "vn %.4lf %.4lf %.4lf", vn.getX(), vn.getY(), vn.getZ());
		stream << s << std::endl;
	}

	for (unsigned int i = 0; i < faces.size(); ++i ){
		auto f = faces[i];
		const auto i1 = f->getV1()->getId() + 1;
		const auto i2 = f->getV2()->getId() + 1;
		const auto i3 = f->getV3()->getId() + 1;

		stream
			<< "f "
			<< i1 << "/" << "/" << i1 << " "
			<< i2 << "/" << "/" << i2 << " "
			<< i3 << "/" << "/" << i3 << std::endl;
	}
	return stream.good();
}

bool OBJFile::containsGroup(std::istream& stream) const
{
	while (!stream.eof()) {
		std::string str;
		std::getline(stream, str);
		if (!str.empty() && str.front() == 'g') {
			return true;
		}
	}
	return false;
}
