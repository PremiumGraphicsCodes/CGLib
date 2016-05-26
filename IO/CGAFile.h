#ifndef __CRYSTAL_IO_CGA_FILE_H__
#define __CRYSTAL_IO_CGA_FILE_H__

#include "File.h"
#include "../Polygon/Actor.h"

namespace Crystal {
	namespace IO {

class CGAFile
{
public:
	CGAFile() = default;

	explicit CGAFile(const std::vector<Core::Actor*>& actors) :
		actors(actors)
	{}

	bool read(const File& file);

	bool read(std::istream& stream);

	bool write(const File& file);

	bool write(std::ostream& stream);

	std::vector<Core::Actor*> getActors() const { return actors; }

private:
	std::vector<Core::Actor*> actors;
};
	}
}

#endif