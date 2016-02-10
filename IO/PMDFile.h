#ifndef __CRYSTAL_IO_PMD_FILE_H__
#define __CRYSTAL_IO_PMD_FILE_H__

#include <vector>
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Polygon {
		class PolygonObject;
	}
	namespace IO {


struct PMDHeader
{
	PMDHeader();

	PMDHeader(const std::string& modelName, const std::string& comment);

	bool read(std::istream& stream);

	bool write(std::ostream& stream);

private:
	std::string magic;
	float version;
	std::string modelName;
	std::string comment;

};

struct PMDVertex
{
	Math::Vector3d<float> pos;
	Math::Vector3d<float> normal;
	Math::Vector2d<float> texCoord;
	std::array< unsigned short, 2> boneNumers;
	char boneWeight; // [0,100]
	char isEdge;

	bool read(std::istream& stream);

	bool write(std::ostream& stream);
};


class PMDMaterial
{

};

class PMDMaterials
{
	int materialCount;
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

struct PMDBone
{
	std::string name;
	unsigned short parentBoneIndex;
	unsigned short tailBoneIndex;
	char type;
	unsigned short ikParentBoneIndex;
	Math::Vector3d<float> boneHeadPos;

	bool read(std::istream& stream);
};

class PMDBones
{
public:
	bool read(std::istream& stream);

private:
	unsigned short boneCount;
	std::vector<PMDBone> bones;
};

class PMDFile
{
public:
	PMDFile() {};

	/*
	PMDFile(const PMDHeader& header,const PMDVertices& vertices, const PMDFaces& faces) :
		header(header),
		vertices(vertices),
		faces(faces)
	{}
	*/

	bool read(const std::string& filename);

	Polygon::PolygonObject* toPolygonObject() const;

private:
	PMDHeader header;
	std::vector<PMDVertex> vertices;
	std::vector<unsigned short> vIndices;
};
	}
}

#endif
