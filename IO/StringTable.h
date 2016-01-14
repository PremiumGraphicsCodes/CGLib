#ifndef __CRYSTAL_IO_STRING_TABLE_H__
#define __CRYSTAL_IO_STRING_TABLE_H__

#include <map>
#include <string>
#include <cassert>

#include "KeyStringMap.h"

#include "../Util/File.h"

namespace Crystal {
	namespace IO {


class StringTable
{
public:


	StringTable();

	void changeLocale(const std::string& l) {
		this->currentLocale = l;
	}

	void add(const std::string key, const std::string value);

	std::string get(const std::string key) { return map[currentLocale].get(key); }

	bool read(const Crystal::File& file);

	bool write(const std::string& folder, const std::string& file);

private:
	std::string currentLocale;
	std::map< std::string, KeyStringMap > map;
};
	}
}

#endif
