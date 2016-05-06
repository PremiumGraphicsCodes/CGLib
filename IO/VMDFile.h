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

	bool write(std::ostream& stream) const;

private:
	char header[30];
	char modelName[20];
};

class VMDMotion
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	char boneName[15];
	DWORD frameNumber;
	float location[3];
	float rotation[4];
	BYTE interpolation[64];
};

class VMDSkin
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	char name[15];
	DWORD frameNumber;
	float weight;
};

class VMDCamera
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	DWORD flameNumber;
	float length;
	float location[3];
	float rotation[3];
	BYTE interpolation[24];
	DWORD viewAngle;
	BYTE perspective;
};

class VMDLight
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	DWORD flameNumber;
	float rgb[3];
	float location[3];
};

class VMDSelfShadow
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	DWORD frameNumber;
	BYTE mode;
	float distance;
};

class VMDFile
{
public:
	bool read(const std::string& filename);

	bool write(const std::string& filename) const;

private:
	VMDHeader header;
	std::vector<VMDMotion> motions;
	std::vector<VMDSkin> skins;
	std::vector<VMDCamera> cameras;
	std::vector<VMDLight> lights;
	std::vector<VMDSelfShadow> selfShadows;
};


	}
}

#endif