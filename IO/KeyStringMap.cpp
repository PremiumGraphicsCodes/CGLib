#include "KeyStringMap.h"

#include <fstream>

using namespace Crystal::IO;

void KeyStringMap::add(const std::string& key, const std::string& value)
{
	map[key] = value;
}

bool KeyStringMap::read(const Crystal::File& file)
{
	std::ifstream stream(file.getFullPath());
	if (!stream.is_open()) {
		return false;
	}
	while( !stream.eof() ) {
		std::string key;
		stream >> key;
		std::string value;
		stream >> value;
		map[key] = value;
	}
	return true;
}

bool KeyStringMap::write(const Crystal::File& file) const
{
	std::ofstream stream(file.getFullPath());
	if (!stream.is_open()) {
		return false;
	}
	for (const auto& m : map) {
		stream << m.first << " " << m.second << std::endl;
	}
	return true;
}
