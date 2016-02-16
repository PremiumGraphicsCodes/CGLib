#include "PMDFile.h"


#include "../Polygon/PolygonObject.h"
#include "../Polygon/ActorObject.h"
#include "../Polygon/Bone.h"
#include "../Polygon/Joint.h"

#include <ostream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Polygon;
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

PMDVertex::PMDVertex(const Vertex& v)
{
	this->pos = v.getPosition();
	this->normal = v.getNormal();
	this->texCoord = Vector2d<float>( v.getTexCoord().getX(), v.getTexCoord().getY() );
}

Vertex PMDVertex::toVertex(const unsigned int id)
{
	Vector3d<float> t(this->texCoord.getX(), this->texCoord.getY(), 0.0f);
	return Vertex(id, this->pos, this->normal, t);
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

bool PMDMaterial::read(std::istream& stream)
{
	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	float alpha = 0.0f;
	stream.read((char*)&red, sizeof(red));
	stream.read((char*)&green, sizeof(green));
	stream.read((char*)&blue, sizeof(blue));
	stream.read((char*)&alpha, sizeof(alpha));
	diffuse = ColorRGBA<float>(red, green, blue, alpha);
	stream.read((char*)&specularity, sizeof(specularity));

	stream.read((char*)&red, sizeof(red));
	stream.read((char*)&green, sizeof(green));
	stream.read((char*)&blue, sizeof(blue));
	specular = ColorRGBA<float>(red, green, blue, 1.0f);

	stream.read((char*)&red, sizeof(red));
	stream.read((char*)&green, sizeof(green));
	stream.read((char*)&blue, sizeof(blue));
	ambient = ColorRGBA<float>(red, green, blue, 1.0f);

	stream.read((char*)&toonIndex, sizeof(toonIndex));
	stream.read((char*)&isEdge, sizeof(isEdge));
	stream.read((char*)&faceVertexCount, sizeof(faceVertexCount));
	char textureFileName[20];
	stream.read(textureFileName, sizeof(textureFileName));

	return stream.good();
}


bool PMDBone::read(std::istream& stream)
{
	char name[20];
	stream.read(name, 20);
	this->name = name;
	stream.read((char*)&parentBoneIndex, sizeof(parentBoneIndex));
	stream.read((char*)&tailBoneIndex, sizeof(tailBoneIndex));
	stream.read((char*)&type, sizeof(type));
	stream.read((char*)&ikParentBoneIndex, sizeof(ikParentBoneIndex));

	float posx = 0.0f;
	stream.read((char*)&posx, sizeof(float));
	float posy = 0.0f;
	stream.read((char*)&posy, sizeof(float));
	float posz = 0.0f;
	stream.read((char*)&posz, sizeof(float));
	this->boneHeadPos = Vector3d<float>(posx, posy, posz);
	return stream.good();
}

/*
Bone PMDBone::toActorBone() const
{
	Bone bone()
}
*/

Joint PMDBone::toJoint() const
{
	return Joint(boneHeadPos);
}

bool PMDBoneCollection::read(std::istream& stream)
{
	short int boneCount = 0;
	stream.read((char*)&boneCount, sizeof(boneCount));
	for (auto i = 0; i < boneCount; ++i) {
		PMDBone bone;
		bone.read(stream);
		bones.emplace_back(bone);
	}
	return stream.good();
}

ActorObject* PMDBoneCollection::toActorObject() const
{
	ActorObject* object = new ActorObject();
	std::vector<Joint*> joints;
	for (size_t i = 0; i < bones.size(); ++i) {
		//vertices.push_back(new Vertex());
		//bones[i].toJoint();
		auto j = object->createJoint(bones[i].boneHeadPos);
		joints.emplace_back(j);
	}
	for (size_t i = 0; i < bones.size(); ++i) {
		const auto parentBoneIndex = bones[i].parentBoneIndex;
		Joint* headJoint = nullptr;
		if (parentBoneIndex != 0xFFFF) {
			headJoint = joints[parentBoneIndex];
		}
		const auto tailBoneIndex = bones[i].tailBoneIndex;
		Joint* tailJoint = nullptr;
		if (tailBoneIndex != 0xFFFF) {
			if (tailBoneIndex != 0) {
				tailJoint = joints[tailBoneIndex];
			}
		}
		object->createBone(headJoint, tailJoint);
	}
	return object;
}


#include <fstream>

PMDFile::PMDFile(const PolygonObject& polygon)
{
	const auto& vs = polygon.getVertices();
	for (auto v : vs) {
		PMDVertex pmdv(*v);
		vertices.push_back(pmdv);
	}
	const auto& fs = polygon.getFaces();
	for (auto f : fs) {
		 faces.push_back( f->getV1()->getId() );
		 faces.push_back( f->getV2()->getId() );
		 faces.push_back( f->getV3()->getId() );
	}
}


bool PMDFile::read(const std::string& filename)
{
	std::ifstream stream(filename, std::ios::binary);
	header.read(stream);
	int vertexCount = 0;
	stream.read((char*)&vertexCount, sizeof(vertexCount));
	for (auto i = 0; i < vertexCount; ++i) {
		PMDVertex vertex;
		vertex.read(stream);
		vertices.emplace_back(vertex);
	}

	stream.read((char*)&vertexCount, sizeof(vertexCount));
	for (auto i = 0; i < vertexCount; ++i) {
		unsigned short vindex = 0;
		stream.read((char*)&vindex, sizeof(vindex));
		faces.push_back(vindex);
	}

	int materialCount = 0;
	stream.read((char*)&materialCount, sizeof(materialCount));
	for (auto i = 0; i < materialCount; ++i) {
		PMDMaterial material;
		material.read(stream);
		materials.emplace_back(material);
	}

	bones.read(stream);

	//bones.read(stream);

	return stream.good();
}


/*
void PMDFile::add(const ActorObject& actor)
{
	actor.get
}
*/

PolygonObject* PMDFile::toPolygonObject() const
{
	PolygonObject* object = new PolygonObject();
	auto vs = this->vertices;
	for (size_t i = 0; i < vs.size(); ++i ) {
		object->createVertex(vs[i].pos, vs[i].normal);
	}
	auto is = this->faces;
	for (size_t i = 0; i < is.size(); i+=3 ) {
		object->createFace(is[i], is[i + 1], is[i + 2]);
	}
	return object;
}

