#ifndef __CRYSTAL_IO_PMD_FILE_H__
#define __CRYSTAL_IO_PMD_FILE_H__

#include <vector>

namespace Crystal {
	namespace IO {

struct PMDHeader
{
	char magic[3];
	float version;
	char model_name[20];
	char comment[256];
};

struct PMDVertex
{
	float pos[3];
	float normal[3];
	float uv[2];
	unsigned short boneNum[2];
	char boneWeight; // [0,100]
	char isEdgeActive;
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

class PMDFile
{

};
	}
}

#endif
