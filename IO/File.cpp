#include "File.h"

using namespace Crystal::IO;

std::string File::getFileName() const
{
	size_t pos = fullpath.rfind('.');
	if (pos == std::string::npos) {
		return "";
	}
	return fullpath.substr(0, pos);
}


std::string File::getExtension() const
{
	size_t pos = fullpath.rfind('.');
	if (pos == std::string::npos) {
		return "";
	}
	return fullpath.substr(pos + 1, fullpath.size());

}
