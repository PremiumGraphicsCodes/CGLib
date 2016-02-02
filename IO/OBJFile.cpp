#define _CRT_SECURE_NO_DEPRECATE

#include "OBJFile.h"

#include <fstream>
#include <cassert>
#include <vector>

#include "../Math/Vector3d.h"
#include "../Polygon/Vertex.h"
#include "../Polygon/TriangleFace.h"

#include "Helper.h"

#include <string>
#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Polygon;
using namespace Crystal::IO;

std::string OBJFace::write(std::ostream& stream) const
{
	std::string s;
	s += "f";
	if ( hasTexIndices() && !hasNormals()) {
		for (size_t i = 0; i < vertexIndices.size(); ++i) {
			s += " " + std::to_string(vertexIndices[i]) + "/" + std::to_string(texIndices[i]);
		}
	}
	else if (hasTexIndices() && hasNormals()) {
		for (size_t i = 0; i < vertexIndices.size(); ++i) {
			s += " " + std::to_string(vertexIndices[i]) + "/" + std::to_string(texIndices[i]) + "/" + std::to_string(normalIndices[i]);
		}
	}
	else if (hasNormals()) {
		for (size_t i = 0; i < vertexIndices.size(); ++i) {
			s += " " + std::to_string(vertexIndices[i]) + "//" + std::to_string(normalIndices[i]);
		}
	}
	else {
		for (const unsigned int i : vertexIndices) {
			s += " " + std::to_string(i);
		}
	}
	return s;
}

OBJFace OBJGroup::readFaces(const std::string& str)
{
	std::vector< std::string >& strs = Helper::split(str, ' ');

	OBJIndices vertexIndices;
	OBJIndices texIndices;
	OBJIndices normalIndices;
	//assert(strs.front() == "f");
	for (unsigned int i = 0; i < strs.size(); ++i) {
		if (strs[i].empty()) {
			continue;
		}
		std::string::size_type pos( strs[i].find("//"));
		if (pos != std::string::npos) {
			strs[i].replace( pos, 2, "/ /");
		}

		std::vector<std::string>& splitted = Helper::split(strs[i], '/');
		const int index = std::stoi(splitted[0]);
		vertexIndices.push_back(index);
		if (splitted.size() >= 2 && splitted[1] != " " ) {
			const int index = std::stoi(splitted[1]);
			texIndices.push_back(index);
		}
		if (splitted.size() >= 3) {
			const int index = std::stoi(splitted[2]);
			normalIndices.push_back(index);
		}
	}
	return OBJFace( vertexIndices, texIndices, normalIndices );
}

TriangleMesh* OBJGroup::createPolygon()
{
	TriangleMesh mesh;
	for (const auto p : positionBuffer) {
		const auto v = mesh.createPosition(p);
	}
	for (auto f : faces) {
		const auto vi = f.getVertexIndices();
		mesh.createFaces(vi);
	}
	return mesh.clone();
}

OBJFile OBJFileReader::read(const std::string& path, const std::string& filename)
{
	const std::string fullPathName = path + "/" + filename;

	std::ifstream stream;
	stream.open(fullPathName.c_str());

	assert(stream.is_open());

	return read(stream);
}


OBJFile OBJFileReader::read(std::istream& stream )
{
	OBJFile file;
	std::string str;

	std::string header = Helper::read< std::string >(stream);

	OBJGroup group;

	std::vector< std::string > materials;

	std::vector<OBJGroup> groups;

	std::vector< Vector3d<float> > positions;
	std::vector< Vector3d<float> > normals;
	std::vector< Vector3d<float> > texCoords;

	std::string useMtlName;
	std::vector<OBJFace> faces;

	while( !stream.eof() ) {
		if( header == "#" ) {
			std::getline( stream, str );
			//header = read< std::string >();
		}
		else if( header == "mtllib" ) {
			std::getline(stream, str);
			OBJMTLLib lib(str);
			group.setMtlLib( lib );
			//libs.push_back(lib);
		}
		else if( header == "v" ) {
			std::getline(stream, str);
			positions.push_back( group.readVertices(str) );
		}
		else if( header == "vt" ) {
			std::getline(stream, str);
			texCoords.push_back( group.readVector3d( str ) );
		}
		else if( header == "vn" || header == "-vn" ) {
			std::getline(stream, str);
			normals.push_back(group.readVector3d(str));
		}
		else if (header == "f") {
			std::getline(stream, str);
			faces.push_back( group.readFaces(str) );
		}
		else if( header == "g") {
			group.setPositions(positions);
			group.setNormals(normals);
			group.setTexCoords(texCoords);
			groups.push_back(group);

			std::getline( stream, str);

			group = OBJGroup();
		}
		else if( header == "usemtl" ) {
			std::getline(stream, str);
			//OBJMaterial material(str);
			const std::string name = str;
			materials.push_back(name);
			useMtlName = name;
		}
		header = Helper::read< std::string >(stream);
	}

	group.setPositions(positions);
	group.setNormals(normals);
	group.setTexCoords(texCoords);
	group.setFaces(faces);
	group.setMaterials(materials);

	groups.push_back(group);

	file.setGroups(groups);
	
	return file;
}


Vector3d<float> OBJGroup::readVertices(const std::string& str)
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

Vector3d<float> OBJGroup::readVector3d(const std::string& str)
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

/*
Vector2d<float> OBJGroup::readVector2d(const std::string& str)
{
	const std::vector< std::string >& strs = Helper::split(str, ' ');
	//assert(strs.front() == "vt");
	assert(strs.size() == 2);
	const float u = ::std::stof(strs[0]);
	const float v = ::std::stof(strs[1]);
	return Vector2d<float>(u, v);
}
*/

bool OBJFileWriter::write(const std::string& path, const std::string& filename, const TriangleMesh& mesh)
{
	const std::string fullPathName = path + "/" + filename;
	std::ofstream stream(fullPathName.c_str());

	if (!stream.is_open()) {
		return false;
	}
	return write(stream, mesh);
}

bool OBJFileWriter::write(std::ostream& stream, const TriangleMesh& mesh)
{
	const auto& positions = mesh.getPositions();
	const auto& normals = mesh.getNormals();
	const auto& faces = mesh.getFaces();

	for (const auto& v : positions) {
		const auto pos = *v;
		char s[256];
		sprintf(s, "v %.4lf %.4lf %.4lf", pos.getX(), pos.getY(), pos.getZ());
		stream << s << std::endl;
	}

	for (const auto& v : normals) {
		const auto vn = *v;
		char s[256];
		sprintf(s, "vn %.4lf %.4lf %.4lf", vn.getX(), vn.getY(), vn.getZ());
		stream << s << std::endl;
	}

	for (const auto& f : faces) {
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
