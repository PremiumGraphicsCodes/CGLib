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

/*
Vertex* OBJVertex::toVertex(const int id) const
{
	return new Vertex(id, )
}

VertexCollection OBJVertexCollection::toVertices() const
{
	for (const auto& v : vertices) {
		v.
	}
}

std::vector<OBJVertexIndex> OBJFile::readFaces(const std::string& str)
{
	std::vector< std::string >& strs = Helper::split(str, ' ');

	OBJVertexIndex vertex;
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
	return vertices;
}
*/

void OBJFile::add(const PolygonObject& polygon)
{
	const auto& vertices = polygon.getVertices();
	for (const auto& v : vertices) {
		this->positions.push_back(v->getPosition());
		this->normals.push_back(v->getNormal());
		this->texCoords.push_back(v->getTexCoord());
	}
	const auto& faces = polygon.getFaces();
	for (const auto& f : faces) {
		const auto index1 = f->getV1()->getId();
		const auto index2 = f->getV2()->getId();
		const auto index3 = f->getV3()->getId();
		this->faceCounts.push_back(3);
	}
}

PolygonObject* OBJFile::toPolygonObject()
{
	PolygonObject* polygon = new PolygonObject();
	std::vector<Vertex*> vv;
	unsigned int currentIndex = 0;
	for(const auto count : faceCounts) {
		for (unsigned int i = 0; i < count; ++i) {
			const auto position = positions[ count + i ];
			const auto normal = normals[ count + i ];
			const auto texCoord = texCoords[ count + i ];
			polygon->createVertex(position, normal, texCoord);
		}
		currentIndex += count;
		polygon->createFaces(vv);
	}
	return polygon;
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
	std::string currentGroupName;
	std::string currentMtllibName;
	std::string currentUseMtlName;

	std::vector< Math::Vector3d<float> > positionBuffer;
	std::vector< Math::Vector3d<float> > texCoordBuffer;
	std::vector< Math::Vector3d<float> > normalBuffer;

	while (!stream.eof()) {
		if (header == "#") {
			std::getline(stream, str);
			//header = read< std::string >();
		}
		else if (header == "v") {
			std::getline(stream, str);
			positionBuffer.push_back(readVertices(str));
		}
		else if (header == "vt") {
			std::getline(stream, str);
			texCoordBuffer.push_back(readVector3d(str));
		}
		else if (header == "vn" || header == "-vn") {
			std::getline(stream, str);
			normalBuffer.push_back(readVector3d(str));
		}
		else if (header == "mtllib") {
			currentMtllibName = Helper::read<std::string>(stream);
			mtllibs.push_back(currentMtllibName);
		}
		else if (header == "usemtl") {
			currentUseMtlName = Helper::read<std::string>(stream);
			//mtllibMap.insert(std::make_pair(currentMtllibName, currentUseMtlName));
		}
		else if (header == "f") {
			std::getline(stream, str);

			std::vector< std::string >& strs = Helper::split(str, ' ');

			//assert(strs.front() == "f");
			for (unsigned int i = 0; i < strs.size(); ++i) {
				if (strs[i].empty()) {
					continue;
				}
				std::string::size_type pos(strs[i].find("//"));
				if (pos != std::string::npos) {
					strs[i].replace(pos, 2, "/ /");
				}

				std::vector<std::string>& splitted = Helper::split(strs[i], '/');
				const int positionIndex = std::stoi(splitted[0]);
				positions.push_back(positionBuffer[positionIndex-1]);

				if (splitted.size() >= 2 && splitted[1] != " ") {
					const int texIndex = std::stoi(splitted[1]);
					texCoords.push_back(texCoordBuffer[texIndex-1]);
				}
				else {
					texCoords.push_back(Vector3d<float>());
				}

				if (splitted.size() >= 3) {
					const int normalIndex = std::stoi(splitted[2]);
					normals.push_back(normalBuffer[normalIndex-1]);
				}
				else {
					normals.push_back(Vector3d<float>());
				}
			}

			const auto count = strs.size();
			faceCounts.push_back( count );
			groupMap[currentGroupName] += count;
			//groupMap.insert(std::make_pair(currentGroupName, f));
			materialMap[currentUseMtlName] += count;
		}
		else if (header == "g") {
			currentGroupName = Helper::read<std::string>(stream);
		}

		header = Helper::read< std::string >(stream);
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
