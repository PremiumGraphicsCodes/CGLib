#ifndef __CRYSTAL_IO_META_LANGUAGE_H__
#define __CRYSTAL_IO_META_LANGUAGE_H__

#include <string>

namespace Crystal {
	namespace IO {

class MetaLanguage
{
public:
	explicit MetaLanguage(const std::string& str)
		: str(str)
	{}

	std::string toStdString() const { return str; }

	private:
		std::string str;
};

	}
}

#endif
