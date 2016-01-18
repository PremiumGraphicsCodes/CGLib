#ifndef __CRYSTAL_UTIL_FILE_SYSTEM_H__
#define __CRYSTAL_UTIL_FILE_SYSTEM_H__

#include <string>

namespace Crystal {

	class File {
	public:
		explicit File(const std::string& filename) : filename(filename)
		{}

		std::string getFullPath() const { return filename; }


	private:
		std::string filename;
	};

}

#endif