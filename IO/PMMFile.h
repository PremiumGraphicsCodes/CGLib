#ifndef __CRYSTAL_IO_PMM_FILE_H__
#define __CRYSTAL_IO_PMM_FILE_H__

#include <istream>
#include <ostream>

namespace Crystal {
	namespace IO {

using DWORD = unsigned long;
using BYTE = unsigned char;
using WORD = unsigned short;

class PMMHeader
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream);

private:
	char formatId[30];
	int viewWidth;
	int viewHeight;
	int frameWidth;
	float viewAngle;
	BYTE flag[7];
};

class PMMModel
{
private:
	int number;

};

class PMMFile
{
public:

private:
	PMMHeader header;
};
	}
}

#endif