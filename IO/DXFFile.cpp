#include "DXFFile.h"

#include <iostream>
#include <string>

using namespace Crystal::Math;
using namespace Crystal::IO;

void DXFFile::read(std::istream& stream)
{
	std::string str;
	std::getline(stream, str);
	const int is0 = std::stoi(str);
	assert(is0 == 0);

	std::getline( stream, str);
	assert( str == "SECTION" );

	std::getline(stream, str);
	const int is2 = std::stoi(str);
	assert(is2 == 2);

	std::getline(stream, str);
	assert(str == "ENTITIES");

	while (str != "EOF") {
		DXFFace f;
		std::getline(stream, str);
		Vector3dVector<float> positions;
		Vector3d<float> pos;
		if (str == "0") {
			std::getline(stream, str);
			if (str == "3DFACE") {
				;
			}
		}
		else if (str == "8") {
			std::getline(stream, str);
			f.setLayerName( str );
		}
		else if (str == "10") {
			std::getline(stream, str);
			pos.setX( std::stof(str) );
		}
		else if (str == "20") {
			std::getline(stream, str);
			pos.setY( std::stof(str) );
		}
		else if (str == "30") {
			std::getline(stream, str);
			pos.setZ(std::stof(str));
			positions.push_back(pos);
		}
	}
}

void DXFFile::write(std::ostream& stream)
{
	strs = {
		"0",
		"SECTION",
		"2",
		"ENTITIES",
	};

	for (const DXFFace& f : faces) {
		strs.push_back( "0");
		strs.push_back( "3DFACE");
		strs.push_back( "8");
		strs.push_back( f.getLayerName());

		const Vector3d<float>& v0 = f.getPositions()[0];
		strs.push_back( "10");
		strs.push_back( std::to_string(v0.getX()) );
		strs.push_back( "20");
		strs.push_back( std::to_string(v0.getY()) );
		strs.push_back( "30");
		strs.push_back( std::to_string(v0.getZ()) );

		const Vector3d<float>& v1 = f.getPositions()[1];
		strs.push_back( "11");
		strs.push_back( std::to_string(v1.getX()));
		strs.push_back( "21");
		strs.push_back( std::to_string(v1.getY()));
		strs.push_back( "31");
		strs.push_back(std::to_string(v1.getZ()));

		const Vector3d<float>& v2 = f.getPositions()[2];
		strs.push_back( "12");
		strs.push_back( std::to_string(v2.getX()));
		strs.push_back( "22");
		strs.push_back( std::to_string(v2.getY()));
		strs.push_back( "32");
		strs.push_back( std::to_string(v2.getZ()));

		const Vector3d<float>& v3 = f.getPositions()[3];
		strs.push_back(" 13");
		strs.push_back( std::to_string(v2.getX()));
		strs.push_back(" 23");
		strs.push_back( std::to_string(v2.getY()));
		strs.push_back( "33");
		strs.push_back( std::to_string(v2.getZ()));
	}


	std::vector<std::string> endStrs {
		"0",
		"ENDSEC",
		"0",
		"EOF"
	};

	strs.insert(strs.end(), endStrs.begin(), endStrs.end());

	for (const std::string& str : strs) {
		stream << str.c_str() << std::endl;
	}

}