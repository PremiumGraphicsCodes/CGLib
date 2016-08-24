#include "stdafx.h"

#include "OBJFile.h"

#include <fstream>
#include <cassert>
#include <vector>

#include "../Math/Vector3d.h"
#include "../Core/Vertex.h"
#include "../Core/Face.h"

#include "Helper.h"

#include <string>
#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Core;
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

void OBJFile::add(const PolygonMesh& polygon)
{
	const auto& vertices = polygon.getVertices();
	for (const auto& v : vertices) {
		this->positions.push_back(v->getPosition());
		this->normals.push_back(v->getNormal());
		this->texCoords.push_back(v->getParameter());
	}
	const auto& faces = polygon.getFaces();
	for (const auto& f : faces) {
		const auto index1 = f->getV1()->getId();
		const auto index2 = f->getV2()->getId();
		const auto index3 = f->getV3()->getId();
		OBJFace face;
		face.positionIndex.push_back( index1 );
		face.positionIndex.push_back( index2 );
		face.positionIndex.push_back( index3 );
		face.normalIndex.push_back(index1);
		face.normalIndex.push_back(index2);
		face.normalIndex.push_back(index3);
		face.texCoordIndex.push_back(index1);
		face.texCoordIndex.push_back(index2);
		face.texCoordIndex.push_back(index3);

		this->faces.push_back(face);
	}
}

#include "../Core/FaceBuilder.h"

PolygonMesh* OBJFile::toPolygonObject()
{
	std::vector<Vertex*> vertices;
	int currentIndex = 0;
	std::vector<std::vector<Vertex*>> faceVertex;

	for(const auto face : this->faces) {
		std::vector<Vertex*> vs;
		for (int i = 0; i < face.positionIndex.size(); ++i) {
			Vector3d<float> pos = positions[face.positionIndex[i] - 1];
			Vector3d<float> normal;
			if (face.normalIndex[i] != -1) {
				normal = normals[face.normalIndex[i] - 1];
			}
			Vector2d<float> texCoord;
			if (face.texCoordIndex[i] != -1) {
				texCoord = texCoords[face.texCoordIndex[i] - 1];
			}
			vertices.push_back(new Vertex(pos, normal, texCoord));
			vs.push_back(vertices.back());
		}
		faceVertex.push_back(vs);

	}
	PolygonBuilder builder(vertices);
	for (auto fv : faceVertex) {
		builder.createFaces(fv);
	}
	return builder.build();
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
	std::pair< std::string, unsigned int > currentGroup;
	std::string currentMtllibName;
	std::pair< std::string, unsigned int > currentUseMtl;

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
			texCoords.push_back(readVector2d(str));
		}
		else if (header == "vn" || header == "-vn") {
			std::getline(stream, str);
			normals.push_back(readVector3d(str));
		}
		else if (header == "mtllib") {
			currentMtllibName = Helper::read<std::string>(stream);
			mtllibs.push_back(currentMtllibName);
		}
		else if (header == "usemtl") {
			useMtlNames.push_back(currentUseMtl);
			currentUseMtl.first = Helper::read<std::string>(stream);
			currentUseMtl.second = 0;
			//mtllibMap.insert(std::make_pair(currentMtllibName, currentUseMtlName));
		}
		else if (header == "f") {
			std::getline(stream, str);

			std::vector< std::string >& strs = Helper::split(str, ' ');

			OBJFace face;

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
				face.positionIndex.push_back(positionIndex);

				if (splitted.size() >= 2 && splitted[1] != " ") {
					const int texIndex = std::stoi(splitted[1]);
					face.texCoordIndex.push_back(texIndex);
				}
				else {
					face.texCoordIndex.push_back(-1);
				}

				if (splitted.size() >= 3) {
					const int normalIndex = std::stoi(splitted[2]);
					face.normalIndex.push_back(normalIndex);
				}
				else {
					face.normalIndex.push_back(-1);
				}
			}

			faces.push_back(face);
			const auto count = static_cast<unsigned int>(strs.size());
			currentGroup.second += count;
			//groupMap.insert(std::make_pair(currentGroupName, f));
			currentUseMtl.second += count;
		}
		else if (header == "g") {
			groups.push_back(currentGroup);
			currentGroup.first = Helper::read<std::string>(stream);
			currentGroup.second = 0;
		}

		header = Helper::read< std::string >(stream);
	}
	useMtlNames.push_back(currentUseMtl);

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

Vector2d<float> OBJFile::readVector2d(const std::string& str)
{
	const std::vector< std::string >& strs = Helper::split(str, ' ');
	//assert(strs.front() == "vt");
	const float u = ::std::stof(strs[0]);
	const float v = ::std::stof(strs[1]);
	return Vector2d<float>(u, v);
}


bool OBJFile::write(const std::string& path, const std::string& filename, const PolygonRepository& factory)
{
	const std::string fullPathName = path + "/" + filename;
	std::ofstream stream(fullPathName.c_str());

	if (!stream.is_open()) {
		return false;
	}
	return write(stream, factory);
}

bool OBJFile::write(std::ostream& stream, const PolygonRepository& factory)
{
	const auto& vertices = factory.getVertices();
	for (const auto& v : vertices) {
		const auto pos = v->getPosition();
		char s[256];
		sprintf_s(s, "v %.4lf %.4lf %.4lf", pos.getX(), pos.getY(), pos.getZ());
		stream << s << std::endl;
	}
	for (const auto& v : vertices) {
		const auto vn = v->getNormal();
		char s[256];
		sprintf_s(s, "vn %.4lf %.4lf %.4lf", vn.getX(), vn.getY(), vn.getZ());
		stream << s << std::endl;
	}


	for(auto p : factory.getPolygons()) {
		const auto& faces = p->getFaces();
		for (auto f : faces) {
			const auto i1 = f->getV1()->getId() + 1;
			const auto i2 = f->getV2()->getId() + 1;
			const auto i3 = f->getV3()->getId() + 1;

			stream
				<< "f "
				<< i1 << "/" << "/" << i1 << " "
				<< i2 << "/" << "/" << i2 << " "
				<< i3 << "/" << "/" << i3 << std::endl;
		}
	}
	return stream.good();
}

#include "../Graphics/VisualPolygon.h"

VisualPolygon OBJFile::load(const File& file)
{
	read(file);
	auto polygon = toPolygonObject();
	auto visualPolygon = VisualPolygon(polygon);
	for (auto lib : mtllibs) {
		std::string mtlFileName = file.getFolderPath() + lib;
		MTLFile mtlFile;
		mtlFile.read(mtlFileName);

		int startIndex = 0;
		for (auto& n : useMtlNames) {
			if (n.first.empty()) {
				continue;
			}
			auto mat = mtlFile.find(n.first).toMaterial(file.getFolderPath());
			auto count =  (n.second - 2) *3;
			auto endIndex = startIndex + count;
			//mat.setDirectory(file.getFolerPath());
			MaterialMap mm(mat, startIndex, endIndex);
			visualPolygon.setMaterial(mm);
			startIndex += count;
		}
	}
	return visualPolygon;
}