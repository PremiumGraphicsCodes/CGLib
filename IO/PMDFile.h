#ifndef __CRYSTAL_IO_PMD_FILE_H__
#define __CRYSTAL_IO_PMD_FILE_H__

#include <vector>
#include "../Math/Vector3d.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Polygon {
		class Vertex;
		class VertexCollection;
		class FaceCollection;
		class PolygonObject;
		class ActorObject;
		class Bone;
		class Joint;
		class CGModel;
	}
	namespace IO {

		using DWORD = unsigned long;
		using BYTE = unsigned char;
		using WORD = unsigned short;


struct PMDHeader
{
	PMDHeader();

	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	float version;
	char modelName[20];
	char comment[256];

};

class PMDVertex
{
public:
	PMDVertex() = default;

	PMDVertex(const Polygon::Vertex& v);

	Polygon::Vertex toVertex(const unsigned int id);

	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

public:
	Math::Vector3d<float> pos;
	Math::Vector3d<float> normal;
	Math::Vector2d<float> texCoord;
	std::array< unsigned short, 2> boneNumers;
	char boneWeight; // [0,100]
	char isEdge;

};

class PMDVertexCollection
{
public:
	PMDVertexCollection() = default;

	PMDVertexCollection(const Polygon::VertexCollection& vs);

	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	std::vector<PMDVertex> get() const { return vertices; }

private:
	std::vector<PMDVertex> vertices;
};


class PMDFaceCollection
{
public:
	PMDFaceCollection() = default;

	PMDFaceCollection(const Polygon::FaceCollection& faces);

	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	std::vector<WORD> get() const { return faces; }

private:
	std::vector<WORD> faces;
};


class PMDMaterial
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	Graphics::ColorRGBA<float> diffuse;
	float specularity;
	Graphics::ColorRGBA<float> specular;
	Graphics::ColorRGBA<float> ambient;
	unsigned char toonIndex;
	unsigned char isEdge;
	unsigned int faceVertexCount;
	char textureFileName[20];
};
class PMDMaterialCollection
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	std::vector<PMDMaterial> materials;
};

enum class PMDBoneType
{
	ROTATE = 0,
	ROTATE_AND_TRANSLATE = 1,
	IK = 2,
	UNKNOWN = 3,
	UNDER_IK = 4,
	UNDERO_ROTATION = 5,
	IK_DEST = 6,
	INVISIBLE = 7,
	STRAIN = 8,
	ROTATION_MOVE = 9
};

class PMDBone
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	Polygon::Bone toBone() const;

	Polygon::Joint toJoint() const;

	char name[20];
	unsigned short parentBoneIndex;
	unsigned short tailBoneIndex;
	char type;
	unsigned short ikParentBoneIndex;
	Math::Vector3d<float> boneHeadPos;
};

class PMDBoneCollection
{
public:
	PMDBoneCollection()
	{}

	PMDBoneCollection(const std::vector<PMDBone>& bones) :
		bones(bones)
	{}

	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	bool readEnglishNames(std::istream& stream);

	Polygon::ActorObject* toActorObject() const;

	//size_t getSize() const { return bones.size(); }

private:
	std::vector<PMDBone> bones;
	std::vector<std::string> englishNames;
};

class PMDIK
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	WORD boneIndex;
	WORD targetBoneIndex;
	BYTE childrenNumber;
	WORD iterationNumber;
	float limitAngle;
	std::vector<WORD> childBoneIndices;
};

class PMDIKCollection
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	std::vector<PMDIK> iks;
};

class PMDSkinVertex
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	DWORD vertexIndex;
	float position[3];
};

class PMDSkin
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	enum class Type {
		Base = 0,
		EyeBrow = 1,
		Eye = 2,
		Lip = 3,
		Other = 4,
	};

private:
	char name[20];
	DWORD vertexCount;
	char type;
	std::vector<PMDSkinVertex> skinVertices;
};

class PMDSkinCollection
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	size_t size() const { return skins.size(); }


private:
	std::vector<PMDSkin> skins;
};

class PMDDisplayBone
{
public:
	bool read(std::istream& stream);

private:
	WORD boneIndex;
	BYTE dispFrameIndex;
};

class PMDNamesInEnglish
{
public:
	bool read(std::istream& stream);

private:
	std::vector<std::string> boneNamesInEnglish;
	std::vector<std::string> skinNamesInEnglish;
	std::vector<std::string> boneDispNames;
};

class PMDRigidBody
{
public:
	bool read(std::istream& stream);

private:
	char name[20];
	WORD relatedBoneIndex;
	BYTE groupIndex;
	WORD groupTarget;
	BYTE shapeType;
	float width;
	float height;
	float depth;
	float position[3];
	float rotation[3];
	float weight;
	float translateDumpingCoe;
	float rotationDumpingCoe;
	float repulse;
	float friction;
	BYTE rigidType;
};

class PMDRigidJoint
{
public:
	bool read(std::istream& stream);
private:
	char name[20];
	DWORD rigidIndex1;
	DWORD rigidIndex2;
	float position[3];
	float rotation[3];
	float constrainPosition1[3];
	float constrainPosition2[3];
	float constrainAngle1[3];
	float constrainAngle2[3];
	float springPosition[3];
	float springRotation[3];
};

class PMDFile
{
public:
	PMDFile() {};

	PMDFile(const Polygon::PolygonObject& object);

	//void add(const Polygon::PolygonObject& object);

	void add(const Polygon::ActorObject& actor);

	bool read(const std::string& filename);

	bool write(const std::string& filename) const;

	Polygon::PolygonObject* toPolygonObject() const;

	Polygon::ActorObject* toActorObject() const;

	Polygon::CGModel* toCGModel() const;

private:
	PMDHeader header;
	PMDVertexCollection vertices;
	PMDFaceCollection faces;
	PMDMaterialCollection materials;
	PMDBoneCollection bones;
	PMDIKCollection iks;
	PMDSkinCollection skins;
	std::vector<WORD> displaySkinIndices;
	std::vector<std::string> displayBoneNames;
	std::vector<PMDDisplayBone> displayBones;
	PMDNamesInEnglish namesInEnglish;
	std::vector<std::string> toonTextureFileNames;
	std::vector<PMDRigidBody> rigidBodies;
	std::vector<PMDRigidJoint> rigidJoints;
};
	}
}

#endif
