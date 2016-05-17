#ifndef __CRYSTAL_IO_FILE_H__
#define __CRYSTAL_IO_FILE_H__

#include <string>

namespace Crystal {
	namespace IO {

class File
{
public:
	explicit File(const std::string& fullpath) : fullpath(fullpath)
	{}

	std::string getFolerPath() const;

	std::string getFileName() const;

	std::string getFileNameExcludingPath() const;

	std::string getExtension() const;

	std::string getFullPath() const { return fullpath; }


private:
	std::string fullpath;
};

	}
}

#endif