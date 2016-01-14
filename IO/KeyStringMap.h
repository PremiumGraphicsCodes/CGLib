#ifndef __CRYSTAL_IO_KEY_STRING_MAP_H__
#define __CRYSTAL_IO_KEY_STRING_MAP_H__

#include <string>
#include <map>

#include "../Util/File.h"

namespace Crystal {
	namespace IO {


class KeyStringMap
{
public:

	void add(const std::string& key, const std::string& value);

	std::string get(const std::string& key) {
		return map[key];
	}

	bool read(const Crystal::File& file);

	bool write(const Crystal::File& file) const;


private:
	std::map< std::string, std::string > map;
};

	}
}

#endif