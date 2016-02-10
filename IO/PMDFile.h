#ifndef __CRYSTAL_IO_PMD_FILE_H__
#define __CRYSTAL_IO_PMD_FILE_H__

#include <vector>
#include "../Math/Vector3d.h"

namespace Crystal {
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
	Math::Vector2d<float> uv;
	std::array< unsigned short, 2> boneNumers;
	char boneWeight; // [0,100]
	char isEdgeActive;

	bool write(std::ostream& stream);
};

struct PMDVertices
{
	unsigned long vertexCount;
	std::vector<PMDVertex> vertices;
};

struct PMDFaces
{
	unsigned long vertexCount;
	std::vector<unsigned short> vertexIndices;
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
	char name[20];
	unsigned short parentBoneIndex;
	unsigned short tailBoneIndex;
	char type;
	unsigned short ikParentBoneIndex;
	float boneHeadPos[3];
};

class PMDFile
{
public:
	bool read(const std::string& filename);

private:
	PMDHeader header;
};
	}
}

#endif
