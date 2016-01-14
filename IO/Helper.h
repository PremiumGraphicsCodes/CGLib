#ifndef __CRYSTAL_IO_HELPER_H__
#define __CRYSTAL_IO_HELPER_H__

#include "../Math/Vector3d.h"
#include "../Graphics/ColorRGB.h"
#include "../Graphics/ColorRGBA.h"
#include <istream>
#include <sstream>

namespace Crystal {
	namespace IO {

class Helper {
public:
	template<typename T>
	static T read(std::istream& s)
	{
		T val;
		s >> val;
		return val;
	}

	static Math::Vector3d<float> readVector(std::istream& s)
	{
		float x, y, z;
		s >> x >> y >> z;
		return Math::Vector3d<float>( x, y, z );
	}

	static Graphics::ColorRGB<float> readColorRGB(std::istream& s)
	{
		float r, g, b;
		s >> r >> g >> b;
		return Graphics::ColorRGB<float>(r, g, b);
	}


	static Graphics::ColorRGBA<float> readColorRGBA(std::istream& s)
	{
		float r, g, b, a;
		s >> r >> g >> b >> a;
		return Graphics::ColorRGBA<float>(r,g,b,a);
	}

	static std::string readNextString(std::istream& stream)
	{
		std::string str = read<std::string>(stream);
		const int size = - static_cast<int>( str.size() );
		stream.seekg( size, std::ios_base::cur);
		return str;
	}

	static std::vector< std::string > split(const std::string& str, char delim){
		/*std::istringstream iss(str);
		std::string tmp;
		std::vector< std::string > res;
		while( getline(iss, tmp, delim) ) {
		res.push_back(tmp);
		}
		return res;*/
		//int a = str.find( delim );
		std::vector< std::string > res;
		std::string tmp;
		for (std::string::const_iterator iter = str.begin(); iter != str.end(); ++iter) {
			if (*iter != delim) {
				tmp += *iter;
			}
			else {
				if (!tmp.empty()) {
					res.push_back(tmp);
				}
				tmp.clear();
			}
		}
		res.push_back(tmp);
		return res;
	}

};

	}
}

#endif