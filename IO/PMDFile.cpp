#include "PMDFile.h"

#include "../Core/PolygonMesh.h"
#include "../Core/Actor.h"
#include "../Core/Bone.h"
#include "../Core/Joint.h"
#include "../Core/CGModel.h"

#include "../Graphics/Material.h"
#include "../Graphics/VisualPolygon.h"

#include <ostream>
#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Core;
using namespace Crystal::IO;

PMDHeader::PMDHeader() :
version(1.0f)
{
}


bool PMDHeader::read(std::istream& stream)
{
	char magic[3];
	stream.read(magic, 3);
	//assert(magic == "Pmd");
	stream.read((char*)&version, sizeof(version));
	stream.read(modelName, sizeof(modelName));
	stream.read(comment, sizeof(comment));
	return stream.good();
}

bool PMDHeader::readEnglishPart(std::istream& stream)
{
	stream.read((char*)&englishNameCompatibility, sizeof(englishNameCompatibility));
	stream.read(modelNameInEnglish, sizeof(modelNameInEnglish));
	stream.read(commentInEnglish, sizeof(commentInEnglish));
	return stream.good();
}

bool PMDHeader::writeEnglishPart(std::ostream& stream) const
{
	stream.write((char*)&englishNameCompatibility, sizeof(englishNameCompatibility));
	stream.write(modelNameInEnglish, sizeof(modelNameInEnglish));
	stream.write(commentInEnglish, sizeof(commentInEnglish));
	return stream.good();
}

bool PMDHeader::write(std::ostream& stream) const
{
	stream.write("Pmd", 3);
	stream.write((char *)&version, sizeof(version));
	stream.write(modelName, 20);
	stream.write(comment, 256);
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

PMDVertexCollection::PMDVertexCollection(const VertexCollection& vs)
{
	for (auto v : vs) {
		PMDVertex pmdv(*v);
		vertices.push_back(pmdv);
	}
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

	stream.read((char*)&boneNumers[0], sizeof(boneNumers[0]));
	stream.read((char*)&boneNumers[1], sizeof(boneNumers[1]));
	stream.read((char*)&boneWeight, sizeof(boneWeight));
	stream.read((char*)&isEdge, sizeof(isEdge));

	return stream.good();
}

bool PMDVertex::write(std::ostream& stream) const
{
	const auto& poss = pos.toArray3();
	stream.write((char *)poss.data(), sizeof(poss));

	const auto& norms = normal.toArray3();
	stream.write((char *)norms.data(), sizeof(norms));

	float u = texCoord.getX();
	float v = texCoord.getY();
	stream.write((char*)&u, sizeof(u));
	stream.write((char*)&v, sizeof(v));

	stream.write((char*)&boneNumers[0], sizeof(boneNumers[0]));
	stream.write((char*)&boneNumers[1], sizeof(boneNumers[1]));
	stream.write((char*)&boneWeight, sizeof(boneWeight));
	stream.write((char*)&isEdge, sizeof(isEdge));

	return stream.good();
}

bool PMDVertexCollection::read(std::istream& stream)
{
	DWORD vertexCount = 0;
	stream.read((char*)&vertexCount, sizeof(vertexCount));
	for (DWORD i = 0; i < vertexCount; ++i) {
		PMDVertex vertex;
		vertex.read(stream);
		vertices.emplace_back(vertex);
	}
	return stream.good();
}

bool PMDVertexCollection::write(std::ostream& stream) const
{
	const auto vertexCount = static_cast<DWORD>(vertices.size());
	stream.write((char*)&vertexCount, sizeof(vertexCount));
	for (DWORD i = 0; i < vertexCount; ++i) {
		vertices[i].write(stream);
	}
	return stream.good();
}

PMDFaceCollection::PMDFaceCollection(const FaceCollection& fs)
{
	for (auto f : fs) {
		faces.push_back(f->getV1()->getId());
		faces.push_back(f->getV2()->getId());
		faces.push_back(f->getV3()->getId());
	}
}

bool PMDFaceCollection::read(std::istream& stream)
{
	DWORD vertexCount = 0;
	stream.read((char*)&vertexCount, sizeof(vertexCount));
	for (DWORD i = 0; i < vertexCount; ++i) {
		unsigned short vindex = 0;
		stream.read((char*)&vindex, sizeof(vindex));
		faces.push_back(vindex);
	}
	return stream.good();
}

bool PMDFaceCollection::write(std::ostream& stream, DWORD vertexCount) const
{
	stream.write((char*)&vertexCount, sizeof(vertexCount));
	for (DWORD i = 0; i < vertexCount; ++i) {
		unsigned short vindex = faces[i];
		stream.write((char*)&vindex, sizeof(vindex));
	}
	return stream.good();
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
	
	stream.read(textureFileName, sizeof(textureFileName));

	return stream.good();
}

bool PMDMaterial::write(std::ostream& stream) const
{
	float red = diffuse.getRed();
	float green = diffuse.getGreen();
	float blue = diffuse.getBlue();
	float alpha = diffuse.getAlpha();
	stream.write((char*)&red, sizeof(red));
	stream.write((char*)&green, sizeof(green));
	stream.write((char*)&blue, sizeof(blue));
	stream.write((char*)&alpha, sizeof(alpha));

	red = specular.getRed();
	green = specular.getGreen();
	blue = specular.getBlue();
	stream.write((char*)&red, sizeof(red));
	stream.write((char*)&green, sizeof(green));
	stream.write((char*)&blue, sizeof(blue));

	red = ambient.getRed();
	green = ambient.getGreen();
	blue = ambient.getBlue();
	stream.write((char*)&red, sizeof(red));
	stream.write((char*)&green, sizeof(green));
	stream.write((char*)&blue, sizeof(blue));

	stream.write((char*)&toonIndex, sizeof(toonIndex));
	stream.write((char*)&isEdge, sizeof(isEdge));
	stream.write((char*)&faceVertexCount, sizeof(faceVertexCount));

	stream.write(textureFileName, sizeof(textureFileName));

	return stream.good();
}


Material PMDMaterial::toMaterial(const std::string& folderName) const
{
	Material material;
	material.setAmbient(this->ambient);
	material.setDiffuse(this->diffuse);
	material.setSpecular(this->specular);
	material.setShininess(this->specularity);
	Texture texture;
	if (!std::string(textureFileName).empty()) {
		Texture diffuseTex(folderName + this->textureFileName);
	}
	material.setTexture(texture);
	return material;
}

bool PMDMaterialCollection::read(std::istream& stream)
{
	int materialCount = 0;
	stream.read((char*)&materialCount, sizeof(materialCount));
	for (auto i = 0; i < materialCount; ++i) {
		PMDMaterial material;
		material.read(stream);
		materials.emplace_back(material);
	}
	return stream.good();
}

bool PMDMaterialCollection::write(std::ostream& stream) const
{
	int materialCount = static_cast<int>(materials.size());
	stream.write((char*)&materialCount, sizeof(materialCount));
	for (auto& m : materials) {
		m.write(stream);
	}
	return stream.good();
}

std::vector<MaterialMap> PMDMaterialCollection::toMaterialMap(const std::string& foldername) const
{
	std::vector<MaterialMap> results;
	auto startIndex = 0;
	for (auto& m : materials) {
		auto endIndex = startIndex + m.getFaceVertexCount();
		MaterialMap mm( m.toMaterial(foldername), startIndex, endIndex);
		startIndex = endIndex;
		results.emplace_back(mm);
	}
	return results;
}

PMDBone::PMDBone(const Bone& bone)
{
	strcpy_s( name, bone.getName().c_str() );
	strcpy_s(englishName, name);
	parentBoneIndex = bone.getOriginJoint()->getId();
	tailBoneIndex = bone.getDestJoint()->getId();
	type = 0;
	ikParentBoneIndex = 0;

	auto pos = bone.getOriginJoint()->getPosition();
	this->boneHeadPos = pos;
}


bool PMDBone::read(std::istream& stream)
{
	stream.read(name, sizeof(name));
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

bool PMDBone::write(std::ostream& stream) const
{
	stream.write(name, sizeof(name));
	stream.write((char*)&parentBoneIndex, sizeof(parentBoneIndex));
	stream.write((char*)&tailBoneIndex, sizeof(tailBoneIndex));
	stream.write((char*)&type, sizeof(type));
	stream.write((char*)&ikParentBoneIndex, sizeof(ikParentBoneIndex));

	float posx = boneHeadPos.getX();
	stream.write((char*)&posx, sizeof(float));
	float posy = boneHeadPos.getY();
	stream.write((char*)&posy, sizeof(float));
	float posz = boneHeadPos.getZ();
	stream.write((char*)&posz, sizeof(float));
	return stream.good();
}

bool PMDBone::readEnglishName(std::istream& stream)
{
	stream.read(englishName, sizeof(englishName));
	return stream.good();
}

bool PMDBone::writeEnglishName(std::ostream& stream) const
{
	stream.write(englishName, sizeof(englishName));
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
	return Joint(boneHeadPos, Vector3d<float>(0.5,0.5, 0.5));
}

PMDBoneCollection::PMDBoneCollection(const Actor& actor)
{
	auto bones = actor.getBones();
	for (auto b : bones) {
		this->bones.push_back(PMDBone(*b));
	}
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

bool PMDBoneCollection::write(std::ostream& stream) const
{
	short int boneCount = static_cast<short int>( bones.size() );
	stream.write((char*)&boneCount, sizeof(boneCount));
	for (auto i = 0; i < boneCount; ++i) {
		bones[i].write(stream);
	}
	return stream.good();
}


bool PMDBoneCollection::readEnglishNames(std::istream& stream)
{
	for (size_t i = 0; i < bones.size(); ++i) {
		bones[i].readEnglishName(stream);
	}
	return stream.good();
}

bool PMDBoneCollection::writeEnglishNames(std::ostream& stream) const
{
	for (size_t i = 0; i < bones.size(); ++i) {
		bones[i].writeEnglishName(stream);
	}
	return stream.good();
}


Actor* PMDBoneCollection::toActorObject() const
{
	Actor* object = new Actor();
	std::vector<Joint*> joints;
	for (size_t i = 0; i < bones.size(); ++i) {
		//vertices.push_back(new Vertex());
		//bones[i].toJoint();
		auto j = object->createJoint(bones[i].boneHeadPos, Vector3d<float>( 0.5, 0.5, 0.5));
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
		object->createBone(headJoint, tailJoint, Vector2d<float>(0.2f, 0.1f));
	}
	return object;
}

bool PMDIK::read(std::istream& stream)
{
	stream.read((char*)&boneIndex, sizeof(boneIndex));
	stream.read((char*)&targetBoneIndex, sizeof(targetBoneIndex));
	stream.read((char*)&childrenNumber, sizeof(childrenNumber));
	stream.read((char*)&iterationNumber, sizeof(iterationNumber));
	stream.read((char*)&limitAngle, sizeof(limitAngle));
	for (int i = 0; i < childrenNumber; ++i) {
		unsigned short childBoneIndex;
		stream.read((char*)&childBoneIndex, sizeof(childBoneIndex));
		childBoneIndices.emplace_back(childBoneIndex);
	}

	return stream.good();
}

bool PMDIK::write(std::ostream& stream) const
{
	stream.write((char*)&boneIndex, sizeof(boneIndex));
	stream.write((char*)&targetBoneIndex, sizeof(targetBoneIndex));
	stream.write((char*)&childrenNumber, sizeof(childrenNumber));
	stream.write((char*)&iterationNumber, sizeof(iterationNumber));
	stream.write((char*)&limitAngle, sizeof(limitAngle));
	for (size_t i = 0; i < childBoneIndices.size(); ++i) {
		unsigned short childBoneIndex = childBoneIndices[i];
		stream.write((char*)&childBoneIndex, sizeof(childBoneIndex));
	}

	return stream.good();
}

bool PMDIKCollection::read(std::istream& stream)
{
	unsigned short ikCount = 0;
	stream.read((char*)&ikCount, sizeof(ikCount));
	for (auto i = 0; i < ikCount; ++i) {
		PMDIK ik;
		ik.read(stream);
		iks.emplace_back(ik);
	}

	return stream.good();
}

bool PMDIKCollection::write(std::ostream& stream) const
{
	unsigned short ikCount = 0;
	stream.write((char*)&ikCount, sizeof(ikCount));
	for (auto i = 0; i < ikCount; ++i) {
		iks[i].write(stream);
	}
	return stream.good();
}

bool PMDSkinVertex::read(std::istream& stream)
{
	stream.read((char*)&vertexIndex, sizeof(vertexIndex));
	stream.read((char*)&position, sizeof(position));
	return stream.good();
}

bool PMDSkinVertex::write(std::ostream& stream) const
{
	stream.write((char*)&vertexIndex, sizeof(vertexIndex));
	stream.write((char*)&position, sizeof(position));
	return stream.good();
}


bool PMDSkin::read(std::istream& stream)
{
	stream.read(name, sizeof(name));
	stream.read((char*)&vertexCount, sizeof(vertexCount));
	stream.read(&type, sizeof(type));
	for (unsigned int i = 0; i < vertexCount; ++i) {
		PMDSkinVertex skinVertex;
		skinVertex.read(stream);
		skinVertices.emplace_back(skinVertex);
		
		//if (type == 0) {

		//}
	}
	return stream.good();
}

bool PMDSkin::write(std::ostream& stream) const
{
	stream.write(name, sizeof(name));
	stream.write((char*)&vertexCount, sizeof(vertexCount));
	stream.write(&type, sizeof(type));
	for (unsigned int i = 0; i < vertexCount; ++i) {
		skinVertices[i].write(stream);
	}
	return stream.good();

}

bool PMDSkinCollection::read(std::istream& stream)
{
	WORD skinCount = 0;
	stream.read((char*)&skinCount, sizeof(skinCount));
	for (unsigned int i = 0; i < skinCount; ++i) {
		PMDSkin skin;
		skin.read(stream);
		skins.emplace_back(skin);
	}
	return stream.good();
}

bool PMDSkinCollection::readEnglishNames(std::istream& stream)
{
	if (skins.size() <= 1) {
		return stream.good();
	}
	for (size_t i = 0; i < skins.size() - 1; ++i) {
		char skinName[20];
		stream.read(skinName, sizeof(skinName));
		englishNames.emplace_back(skinName);
	}
	return stream.good();
}

bool PMDSkinCollection::writeEnglishNames(std::ostream& stream) const
{
	for (const auto& name : englishNames) {
		stream.write(name.c_str(), sizeof(name.c_str()));
	}
	return stream.good();
}


bool PMDSkinCollection::write(std::ostream& stream) const
{
	WORD skinCount = static_cast<WORD>(skins.size());
	for (unsigned int i = 0; i < skinCount; ++i) {
		skins[i].write(stream);
	}
	return stream.good();
}

bool PMDDisplaySkinCollection::read(std::istream& stream)
{
	BYTE displaySkinCount = 0;
	stream.read((char*)&displaySkinCount, sizeof(displaySkinCount));
	for (unsigned int i = 0; i < displaySkinCount; ++i) {
		WORD skinIndex;
		stream.read((char*)&skinIndex, sizeof(skinIndex));
		displaySkinIndices.push_back(skinIndex);
	}
	return stream.good();
}

bool PMDDisplaySkinCollection::write(std::ostream& stream) const
{
	BYTE displaySkinCount = static_cast<BYTE>( displaySkinIndices.size() );
	stream.write((char*)&displaySkinCount, sizeof(displaySkinCount));
	for (unsigned int i = 0; i < displaySkinCount; ++i) {
		WORD skinIndex = displaySkinIndices[i];
		stream.write((char*)&skinIndex, sizeof(skinIndex));
	}
	return stream.good();

}

bool PMDDisplayBone::read(std::istream& stream)
{
	stream.read((char*)&boneIndex, sizeof(boneIndex));
	stream.read((char*)&dispFrameIndex, sizeof(dispFrameIndex));
	return stream.good();
}

bool PMDDisplayBone::write(std::ostream& stream) const
{
	stream.write((char*)&boneIndex, sizeof(boneIndex));
	stream.write((char*)&dispFrameIndex, sizeof(dispFrameIndex));
	return stream.good();
}

bool PMDDisplayBoneNameCollection::read(std::istream& stream)
{
	BYTE displayBoneCount = 0;
	stream.read((char*)&displayBoneCount, sizeof(displayBoneCount));
	for (unsigned int i = 0; i < displayBoneCount; ++i) {
		char dispName[50];
		stream.read((char*)&dispName, sizeof(dispName));
		names.push_back(dispName);
	}
	return stream.good();
}

bool PMDDisplayBoneNameCollection::write(std::ostream& stream) const
{
	BYTE displayBoneCount = static_cast<BYTE>(names.size());
	stream.write((char*)&displayBoneCount, sizeof(displayBoneCount));
	for (unsigned int i = 0; i < displayBoneCount; ++i) {
		stream.write(names[i].c_str(), sizeof(names[i]));
	}
	return stream.good();
}

bool PMDDisplayBoneNameCollection::readEnglishNames(std::istream& stream)
{
	for (size_t i = 0; i < names.size(); ++i) {
		char englishName[50];
		stream.read(englishName, sizeof(englishName));
		englishNames.emplace_back(englishName);
	}
	return stream.good();
}

bool PMDDisplayBoneNameCollection::writeEnglishNames(std::ostream& stream) const
{
	for (size_t i = 0; i < names.size(); ++i) {
		stream.write(englishNames[i].c_str(), sizeof(englishNames[i].c_str()));
	}
	return stream.good();
}


bool PMDToonTextures::read(std::istream& stream)
{
	for (int i = 0; i < 10; ++i) {
		char toonTextureFileName[100];
		stream.read(toonTextureFileName, sizeof(toonTextureFileName));
		toonTextureFileNames[i] = toonTextureFileName;
	}
	return stream.good();
}

bool PMDToonTextures::write(std::ostream& stream) const
{
	for (int i = 0; i < 10; ++i) {
		stream.write(toonTextureFileNames[i].c_str(), sizeof(toonTextureFileNames[i].size()));
	}
	return stream.good();
}


bool PMDRigidBody::read(std::istream& stream)
{
	stream.read(name, sizeof(name));
	stream.read((char*)&relatedBoneIndex, sizeof(relatedBoneIndex));
	stream.read((char*)&groupIndex, sizeof(groupIndex));
	stream.read((char*)&groupTarget, sizeof(groupTarget));
	stream.read((char*)&shapeType, sizeof(shapeType));
	stream.read((char*)&width, sizeof(width));
	stream.read((char*)&height, sizeof(height));
	stream.read((char*)&depth, sizeof(depth));
	stream.read((char*)&position, sizeof(position));
	stream.read((char*)&rotation, sizeof(rotation));
	stream.read((char*)&weight, sizeof(weight));
	stream.read((char*)&translateDumpingCoe, sizeof(translateDumpingCoe));
	stream.read((char*)&rotationDumpingCoe, sizeof(rotationDumpingCoe));
	stream.read((char*)&repulse, sizeof(repulse));
	stream.read((char*)&friction, sizeof(friction));
	stream.read((char*)&rigidType, sizeof(rigidType));
	return stream.good();
}

bool PMDRigidBody::write(std::ostream& stream) const
{
	stream.write(name, sizeof(name));
	stream.write((char*)&relatedBoneIndex, sizeof(relatedBoneIndex));
	stream.write((char*)&groupIndex, sizeof(groupIndex));
	stream.write((char*)&groupTarget, sizeof(groupTarget));
	stream.write((char*)&shapeType, sizeof(shapeType));
	stream.write((char*)&width, sizeof(width));
	stream.write((char*)&height, sizeof(height));
	stream.write((char*)&depth, sizeof(depth));
	stream.write((char*)&position, sizeof(position));
	stream.write((char*)&rotation, sizeof(rotation));
	stream.write((char*)&weight, sizeof(weight));
	stream.write((char*)&translateDumpingCoe, sizeof(translateDumpingCoe));
	stream.write((char*)&rotationDumpingCoe, sizeof(rotationDumpingCoe));
	stream.write((char*)&repulse, sizeof(repulse));
	stream.write((char*)&friction, sizeof(friction));
	stream.write((char*)&rigidType, sizeof(rigidType));
	return stream.good();
}

bool PMDRigidBodyCollection::read(std::istream& stream)
{
	DWORD rigidBodyCount = 0;
	stream.read((char*)&rigidBodyCount, sizeof(rigidBodyCount));
	for (unsigned int i = 0; i < rigidBodyCount; ++i) {
		PMDRigidBody rigidBody;
		rigidBody.read(stream);
		rigidBodies.emplace_back(rigidBody);
	}
	return stream.good();
}

bool PMDRigidBodyCollection::write(std::ostream& stream) const
{
	DWORD rigidBodyCount = static_cast<DWORD>(rigidBodies.size());
	stream.write((char*)&rigidBodyCount, sizeof(rigidBodyCount));
	for (const auto& b : rigidBodies) {
		b.write(stream);
	}
	return stream.good();
}


bool PMDRigidJoint::read(std::istream& stream)
{
	stream.read(name,sizeof(name));
	stream.read((char*)&rigidIndex1, sizeof(rigidIndex1));
	stream.read((char*)&rigidIndex2, sizeof(rigidIndex2));
	stream.read((char*)&position, sizeof(position));
	stream.read((char*)&rotation, sizeof(rotation));
	stream.read((char*)&constrainPosition1, sizeof(constrainPosition1));
	stream.read((char*)&constrainPosition2, sizeof(constrainPosition2));
	stream.read((char*)&constrainAngle1, sizeof(constrainAngle1));
	stream.read((char*)&constrainAngle2, sizeof(constrainAngle2));
	stream.read((char*)&springPosition, sizeof(springPosition));
	stream.read((char*)&springRotation, sizeof(springRotation));
	return stream.good();
}

bool PMDRigidJoint::write(std::ostream& stream) const
{
	stream.write(name, sizeof(name));
	stream.write((char*)&rigidIndex1, sizeof(rigidIndex1));
	stream.write((char*)&rigidIndex2, sizeof(rigidIndex2));
	stream.write((char*)&position, sizeof(position));
	stream.write((char*)&rotation, sizeof(rotation));
	stream.write((char*)&constrainPosition1, sizeof(constrainPosition1));
	stream.write((char*)&constrainPosition2, sizeof(constrainPosition2));
	stream.write((char*)&constrainAngle1, sizeof(constrainAngle1));
	stream.write((char*)&constrainAngle2, sizeof(constrainAngle2));
	stream.write((char*)&springPosition, sizeof(springPosition));
	stream.write((char*)&springRotation, sizeof(springRotation));
	return stream.good();
}


bool PMDRigidJointCollection::read(std::istream& stream)
{
	DWORD rigidJointCount = 0;
	stream.read((char*)&rigidJointCount, sizeof(rigidJointCount));
	for (unsigned int i = 0; i < rigidJointCount; ++i) {
		PMDRigidJoint joint;
		joint.read(stream);
		joints.emplace_back(joint);
	}
	return stream.good();
}

bool PMDRigidJointCollection::write(std::ostream& stream) const
{
	DWORD rigidJointCount = static_cast<DWORD>(joints.size());
	stream.write((char*)&rigidJointCount, sizeof(rigidJointCount));
	for (const auto& j : joints) {
		j.write(stream);
	}
	return stream.good();

}

bool PMDDisplayBoneCollection::read(std::istream& stream)
{
	DWORD count = 0;
	stream.read((char*)&count, sizeof(count));
	for (unsigned int i = 0; i < count; ++i) {
		PMDDisplayBone dispBone;
		dispBone.read(stream);
		displayBones.emplace_back(dispBone);
	}
	return stream.good();
}

bool PMDDisplayBoneCollection::write(std::ostream& stream) const
{
	DWORD count = static_cast<DWORD>(displayBones.size());
	stream.write((char*)&count, sizeof(count));
	for (const auto& b : displayBones) {
		b.write(stream);
	}
	return stream.good();
}

PMDFile::PMDFile(const VisualPolygon& polygon)
{
	vertices = PMDVertexCollection( polygon.getPolygon()->getVertices() );
	faces = PMDFaceCollection(polygon.getPolygon()->getFaces());
}

void PMDFile::add(const Actor& actor)
{
	bones = PMDBoneCollection(actor);
}

bool PMDFile::read(const std::string& filename)
{
	std::ifstream stream(filename, std::ios::binary);
	if (!stream.is_open()) {
		return false;
	}
	this->filename = filename;
	header.read(stream);
	vertices.read(stream);
	faces.read(stream);
	materials.read(stream);

	bones.read(stream);
	iks.read(stream);
	skins.read(stream);
	displaySkins.read(stream);
	displayBoneNames.read(stream);
	displayBones.read(stream);

	header.readEnglishPart(stream);
	bones.readEnglishNames(stream);
	skins.readEnglishNames(stream);
	displayBoneNames.readEnglishNames(stream);

	toonTextures.read(stream);

	rigidBodies.read(stream);
	rigidJoints.read(stream);

	return stream.eof();
}

bool PMDFile::write(const std::string& filename) const
{
	std::ofstream stream(filename, std::ios::binary);
	if (!stream.is_open()) {
		return false;
	}
	header.write(stream);
	vertices.write(stream);
	faces.write(stream, vertices.get().size());
	materials.write(stream);

	bones.write(stream);
	iks.write(stream);
	skins.write(stream);
	displaySkins.write(stream);
	displayBoneNames.write(stream);
	displayBones.write(stream);

	header.writeEnglishPart(stream);
	bones.writeEnglishNames(stream);
	skins.writeEnglishNames(stream);
	displayBoneNames.writeEnglishNames(stream);

	toonTextures.write(stream);

	rigidBodies.write(stream);
	rigidJoints.write(stream);

	return stream.good();
}


/*
void PMDFile::add(const ActorObject& actor)
{
	actor.get
}
*/

PolygonMesh* PMDFile::toPolygonObject() const
{
	PolygonMesh* object = new PolygonMesh();
	auto vs = this->vertices.get();
	for (size_t i = 0; i < vs.size(); ++i ) {
		object->createVertex(vs[i].pos, vs[i].normal);
	}
	auto is = this->faces.get();
	for (size_t i = 0; i < is.size(); i+=3 ) {
		object->createFace(is[i], is[i + 1], is[i + 2]);
	}
	return object;
}

#include "File.h"

VisualPolygon PMDFile::toVisualPolygon() const
{
	auto p = toPolygonObject();
	VisualPolygon visualPolygon(p);
	Crystal::IO::File f(filename);
	auto mm = materials.toMaterialMap(f.getFolerPath());
	for (const auto& m : mm) {
		visualPolygon.setMaterial(m);
	}
	return visualPolygon;
}


Actor* PMDFile::toActorObject() const
{
	return bones.toActorObject();
}

CGModel* PMDFile::toCGModel() const
{
	return new CGModel(toPolygonObject(), toActorObject());
}
