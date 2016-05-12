#ifndef __CRYSTAL_IO_STL_FILE_H__
#define __CRYSTAL_IO_STL_FILE_H__

#include "../Math/Vector3d.h"
#include "../Polygon/PolygonMesh.h"

#include <fstream>

#include <vector>

namespace Crystal {
	namespace IO {

struct STLCell
{
public:
	STLCell()
	{}

	STLCell(const std::vector< Math::Vector3d<float> >& positions, const Math::Vector3d<float>& normal) :
		positions(positions),
		normal(normal)
	{}


	std::vector< Math::Vector3d<float> > getPositions() const { return positions; }

	void setPositions(const std::vector< Math::Vector3d<float> >& positions) { this->positions = positions; }

	void addPosition(const Math::Vector3d<float>& pos) { this->positions.push_back(pos); }

	void setNormal(const Math::Vector3d<float>& normal) { this->normal = normal; }

	Math::Vector3d<float> getNormal() const { return normal; }

	bool operator==(const STLCell& rhs) const {
		return
			positions == rhs.positions &&
			normal == rhs.normal;
	}


private:
	std::vector< Math::Vector3d<float> > positions;
	Math::Vector3d<float> normal;
};

typedef std::vector< STLCell > STLCellVector;

class STLFile {
public:
	STLFile()
	{}

	STLFile(const STLCellVector& cells, const std::string title) :
		 cells( cells ),
		title( title )
	{

	}

	void add(const Polygon::PolygonMesh& mesh);

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

	Polygon::PolygonMesh* toPolygonObject() const;

private:
	STLCellVector cells;
	std::string title;

	bool readASCII(std::istream& stream);

	bool readBinary(std::istream& stream);
};
	}
}

#endif