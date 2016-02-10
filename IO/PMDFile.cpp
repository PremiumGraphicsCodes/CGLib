#include "PMDFile.h"

#include <ostream>

using namespace Crystal::Math;
using namespace Crystal::IO;

PMDHeader::PMDHeader() :
magic("Pmd"),
version(1.0f)
{
}


PMDHeader::PMDHeader(const std::string& modelName, const std::string& comment) :
	magic("Pmd"),
	version(1.0f),
	modelName(modelName),
	comment(comment)
{
	//assert(modelName.size() <= 20);
	//assert(comment.size() <= 256);
}

/*
namespace {
	std::string readChar(std::istream& stream, int howMany)
	{
		std::vector<char> str(howMany);
		stream.read(str.data(), howMany);
	}
}*/

bool PMDHeader::read(std::istream& stream)
{
	char str[256];
	stream.read(str, 3);
	
	this->magic = str;
	stream.read((char*)&version, sizeof(version));
	stream.read(str, 20);
	this->modelName = str;
	stream.read(str, 256);
	this->comment = str;
	return stream.good();
}


bool PMDHeader::write(std::ostream& stream)
{
	stream.write((char *)magic.c_str(), 3);
	stream.write((char *)&version, sizeof(version));
	stream.write((char *)modelName.c_str(), 20);
	stream.write((char *)comment.c_str(), 256);
	return stream.good();
}

bool PMDVertex::read(std::istream& stream)
{
	float posx = 0.0f;
	stream.read((char*)&posx, sizeof(float));
	float posy = 0.0f;
	stream.read((char*)&posy, sizeof(float));
	float posz = 0.0f;
	stream.read((char*)&posz, sizeof(float));
	this->pos = Vector3d<float>(posx, posy, posz);

	float normx = 0.0f;
	stream.read((char*)&normx, sizeof(float));
	float normy = 0.0f;
	stream.read((char*)&normy, sizeof(float));
	float normz = 0.0f;
	stream.read((char*)&normz, sizeof(float));
	this->normal = Vector3d<float>(normx, normy, normz);

	float u = 0.0f;
	float v = 0.0f;
	stream.read((char*)&u, sizeof(u));
	stream.read((char*)&v, sizeof(v));
	texCoord = Vector2d<float>(u, v);

	stream.read((char*)& boneNumers[0], sizeof(boneNumers[0]));
	stream.read((char*)& boneNumers[1], sizeof(boneNumers[1]));
	stream.read((char*)&boneWeight, sizeof(boneWeight));
	stream.read((char*)&isEdge, sizeof(isEdge));

	return stream.good();
}

bool PMDVertex::write(std::ostream& stream)
{
	const auto poss = pos.toArray3();
	stream.write((char *)poss.data(), sizeof(poss));

	return false;
}

bool PMDVertices::read(std::istream& stream)
{
	stream.read((char*)&vertexCount, sizeof(vertexCount));
	for (auto i = 0; i < vertexCount; ++i) {
		PMDVertex vertex;
		vertex.read(stream);
		vertices.emplace_back(vertex);
	}

	return stream.good();
}


bool PMDFaces::read(std::istream& stream)
{
	stream.read((char*)&vertexCount, sizeof(vertexCount));
	for (auto i = 0; i < vertexCount; ++i) {
		unsigned short vindex = 0;
		stream.read((char*)&vindex, sizeof(vindex));
		this->vertexIndices.push_back(vindex);
		//PMDVertex vertex;
		//vertex.read(stream);
		//vertices.emplace_back(vertex);
	}
	return stream.good();
}


#include <fstream>

bool PMDFile::read(const std::string& filename)
{
	std::ifstream stream(filename, std::ios::binary);
	header.read(stream);
	vertices.read(stream);
	faces.read(stream);

	return stream.good();
}

#include "../Polygon/PolygonObject.h"

using namespace Crystal::Polygon;

PolygonObject* PMDFile::toPolygonObject() const
{
	PolygonObject* object = new PolygonObject();
	auto vs = this->vertices.vertices;
	for (int i = 0; i < vs.size(); ++i ) {
		auto p = object->createPosition(vs[i].pos);
		auto n = object->createNormal(vs[i].normal);
		object->createVertex(p, n);
	}
	auto is = this->faces.vertexIndices;
	for (int i = 0; i < is.size(); i+=3 ) {
		object->createFace(is[i], is[i + 1], is[i + 2]);
	}
	return object;
}
