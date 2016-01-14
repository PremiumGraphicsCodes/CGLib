#include "STLFile.h"

#include "Helper.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

#include <string>
#include <cassert>

bool STLFile::read( const std::string& filename ) {
	std::ifstream stream( filename );

	std::string str0, str1,str2;
	stream >> str0;
	stream >> str1;
	stream >> str2;
	stream.close();

	if( str0 == "solid" && str2 == "facet" ) {
		return readASCII( filename );
	}
	else {
		return readBinary( filename );
	}
}

bool STLFile::readASCII(const std::string& filename) {
	std::ifstream stream;
	stream.open(filename);
	if (!stream.is_open()) {
		return false;
	}
	return readASCII(stream);
}

bool STLFile::readASCII(std::istream& stream)
{
	std::string str = Helper::read<std::string>(stream);

	assert( str == "solid" );

	std::getline(stream, str);

	title = str;

	str = Helper::read<std::string>(stream);
	while( str != "endsolid" ) {
		assert( str == "facet" );
		str = Helper::read<std::string>(stream);
		assert(str == "normal");

		STLCell cell;
		const Vector3d<float>& normal = Helper::readVector(stream);
		cell.setNormal( normal );
			
		stream >> str;
		assert( str == "outer" );

		stream >> str;
		assert( str == "loop" );

		for( int i = 0; i < 3; ++i ) {
			stream >> str;
			assert( str == "vertex" );
				
			const Vector3d<float>& position = Helper::readVector(stream);
			cell.addPosition( position );
		}
		cells.push_back( cell );

		str = Helper::read<std::string>(stream);
		assert( str == "endloop" );

		str = Helper::read<std::string>(stream);
		assert(str == "endfacet");

		str = Helper::read<std::string>(stream);
	}

	return true;
}

bool STLFile::writeASCII(const std::string& filename)
{
	std::ofstream stream;
	stream.open(filename);
	if (!stream.is_open()) {
		return false;
	}

	return writeASCII(stream);
}

bool STLFile::writeASCII(std::ostream& stream)
{
	stream << "solid" << " " << title << std::endl;

	for (const STLCell& cell : cells) {
		stream << "facet" << " ";
		const Vector3d<float>& normal = cell.getNormal();
		stream << "normal" << " " << normal.getX() << " " << normal.getY() << " " << normal.getZ() << std::endl;
		stream << "outer loop" << std::endl;
		const std::vector< Vector3d<float> >& positions = cell.getPositions();
		for (const Vector3d<float>& pos : positions) {
			stream << "vertex" << " " << pos.getX() << " " << pos.getY() << " " << pos.getZ() << std::endl;
		}
		stream << "endloop" << std::endl;
		stream << "endfacet" << std::endl;
	}
	stream << "endsolid" << std::endl;

	return true;
}


bool STLFile::readBinary(const std::string& filename) {
	std::ifstream stream;
	stream.open(filename);
	if (!stream.is_open()) {
		return false;
	}
	return readBinary(stream);
}

bool STLFile::readBinary(std::istream& stream) {
	char head[80];
	stream.read( head, 80 );

	unsigned int howMany;
	stream.read( (char *)&howMany, sizeof(unsigned int) );

	for( size_t i = 0; i < howMany; ++i ) {
		float normal[3];
		stream.read( (char *)&normal, sizeof( float ) * 3 );
		float pos0[3];
		stream.read( (char *)&pos0, sizeof( float ) * 3 );
		float pos1[3];
		stream.read( (char *)&pos1, sizeof( float ) * 3 );
		float pos2[3];
		stream.read( (char *)&pos2, sizeof( float ) * 3 );
		char padding[2];
		stream.read( padding, sizeof( char ) * 2 );

		STLCell cell;
		cell.setNormal( Vector3d<float>( normal[0], normal[1], normal[2] ) );
		cell.addPosition( Vector3d<float>( pos0[0], pos0[1], pos0[2] ) );
		cell.addPosition( Vector3d<float>( pos1[0], pos1[1], pos1[2] ) );
		cell.addPosition( Vector3d<float>( pos2[0], pos2[1], pos2[2] ) );
		//faces.push_back( f );
		cells.push_back( cell );
	}
	return true;
}

bool STLFile::writeBinary(std::ostream& stream)
{
	const char* head = title.c_str();
	stream.write(head, 80);

	const auto howMany = cells.size();
	stream.write( (char *)&howMany, sizeof(unsigned int) );

	for (const STLCell& cell : cells) {
		const std::vector<float>& normal = cell.getNormal().toArray();
		stream.write((char *)&(normal.front()), sizeof(float) * 3);
		for (const Vector3d<float>& pos : cell.getPositions()) {
			const std::vector<float>& p = pos.toArray();
			stream.write((char *)&(p.front()), sizeof(float) * 3);
		}
		char padding[2];
		stream.write(padding, sizeof( char ) * 2);
	}

	return true;
}