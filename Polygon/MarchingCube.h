#ifndef __CRYSTAL_POLYGON_MARCHING_CUBE_H__
#define __CRYSTAL_POLYGON_MARCHING_CUBE_H__


#include "Vertex.h"
#include "../Math/Vector3d.h"
#include "../Math/Space3d.h"
#include "../Math/Volume3d.h"
#include "../Util/UnCopyable.h"
#include "../Math/MarchingCubeTable.h"
#include <vector>
#include <array>

namespace Crystal {
	namespace Math {
		template<typename, typename>
		class Volume3d;
	}

	namespace Polygon {

		class MCEdge;

class PositionValue
{
public:
	PositionValue();

	PositionValue(const Math::Vector3d<float>& p, const float& v);
	
	Math::Vector3d<float> getInterpolatedPosition(const float v, const PositionValue& rhs) const;
	
private:
	Math::Vector3d<float> pos;
	float value;
};


class VolumeCell3d
{
public:
	VolumeCell3d(const Math::Space3d<float>& space, const std::array< float, 8>& values) :
		space(space),
		values(values)
	{}

	Math::Space3d<float> getSpace() const { return space; }

	std::array< float, 8 > getValues() const { return values; }

	std::array< PositionValue, 8 > toPositionValues() const;

private:
	Math::Space3d<float> space;
	std::array< float, 8> values;
};

class MarchingCube final : UnCopyable
{
public:
	MarchingCube() {
		table.buildEdgeTable();
		table.buildTriangleTable();
	}

	~MarchingCube() = default;

	void march(const Math::Volume3d<float, float>& ss, const float isolevel);

	//TriangleMesh* cloneMesh() {mesh->}
	TriangleMesh* cloneMesh() { return mesh.clone(); }

	std::list< Vertex* > getVertices() { return mesh.getVertices(); }

private:
	Math::MarchingCubeTable table;
	TriangleMesh mesh;

	int getCubeIndex(const std::array< float, 8 >& val, const float isolevel) const;

	std::array< Math::Vector3d<float>, 12 > getPositions(const int cubeindex, const VolumeCell3d& cell, const float isolevel) const;

};

	}
}

#endif