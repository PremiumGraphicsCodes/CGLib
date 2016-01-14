#ifndef __CRYSTAL_IO_DXF_FILE_H__
#define __CRYSTAL_IO_DXF_FILE_H__

#include <istream>
#include <cassert>

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {

struct DXFFace{
	void setColorNumber(const int colorNumber) { this->colorNumber = colorNumber; }

	int getColorNumber() const { return colorNumber;  }

	void setPositions(const Math::Vector3dVector<float>& positions) {
		assert( positions.size() == 4 );
		this->positions = positions;
	}

	Math::Vector3dVector<float> getPositions() const { return positions; }

	void setLayerName(const std::string& layerName) { this->layerName = layerName; }

	std::string getLayerName() const { return layerName; }
	
private:
	int colorNumber;
	Math::Vector3dVector<float> positions;
	std::string layerName;
};

typedef std::vector< DXFFace > DXFFaceVector;

class DXFFile{
public:
	DXFFile(){};

	void read(std::istream& stream);

	void write(std::ostream& stream);

	void setFaces(const DXFFaceVector& face) { this->faces = faces; }

	DXFFaceVector getFaces() const { return faces; }

	std::vector< std::string > getStrs() const { return strs; }

private:
	std::vector< std::string > strs;

	DXFFaceVector faces;
};
	}
}

#endif