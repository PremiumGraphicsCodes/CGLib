#ifndef __CRYSTAL_IO_VMD_FILE_H__
#define __CRYSTAL_IO_VMD_FILE_H__

#include <ostream>
#include <istream>
#include <vector>

namespace Crystal {
	namespace IO {

using DWORD = unsigned long;
using BYTE = unsigned char;
using WORD = unsigned short;

class VMDHeader
{
public:
	VMDHeader();

	bool read(std::istream& stream);

	bool write(std::ostream& stream);

private:
	char header[30];
	char modelName[20];
};

class VMDMotion
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream);

private:
	char boneName[15];
	DWORD frameNumber;
	float location[3];
	float rotation[4];
	BYTE interpolation[64];
};

class VMDSkin
{
private:
	//char 
};

class VMDFile
{
public:
	bool read(const std::string& filename);

	bool write(const std::string& filename);

private:
	VMDHeader header;
	std::vector<VMDMotion> motions;
};


	}
}

#endif