#ifndef __CRYSTAL_IO_STL_FILE_H__
#define __CRYSTAL_IO_STL_FILE_H__

#include "STLCell.h"

#include <fstream>

#include <vector>

namespace Crystal {
	namespace IO {

class STLFile {
public:
	STLFile()
	{}

	STLFile(const STLCellVector& cells, const std::string title) :
		 cells( cells ),
		title( title )
	{
	}

	bool isBinary(std::istream& stream);

	bool isAscii(std::istream& stream);

	void add(const Core::PolygonMesh& mesh);

	bool read(const std::string& filename);

	bool read(std::istream& stream);

	bool writeASCII(const std::string& filename);

	bool writeASCII(std::ostream& stream);

	bool writeBinary(std::ostream& stream);

	bool writeBinary(const std::string& filename);

	bool operator==(const STLFile& rhs) const {
		return
			title == rhs.title &&
			cells == rhs.cells;
	}

	Core::PolygonMesh* toPolygonObject() const;

	bool readASCII(std::istream& stream);

	bool readBinary(std::istream& stream);


private:
	STLCellVector cells;
	std::string title;

};
	}
}

#endif