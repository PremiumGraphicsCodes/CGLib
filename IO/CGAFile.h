#ifndef __CRYSTAL_IO_CGA_FILE_H__
#define __CRYSTAL_IO_CGA_FILE_H__

#include "File.h"
#include "../Polygon/Actor.h"

namespace Crystal {
	namespace IO {

class CGAFile
{
public:
	bool read(const File& file);

	bool write(const File& file);

private:
	Polygon::Actor actor;
};
	}
}

#endif