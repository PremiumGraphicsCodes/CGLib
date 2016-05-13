#ifndef __CRYSTAL_GRAPHICS_VISUAL_POLYGON_H__
#define __CRYSTAL_GRAPHICS_VISUAL_POLYGON_H__

#include <vector>
#include "Material.h"
#include "MaterialMap.h"

namespace Crystal{
	namespace Polygon {
		class PolygonMesh;
	}
	namespace Graphics {



class VisualPolygon
{
public:
	VisualPolygon() = default;

	explicit VisualPolygon(Polygon::PolygonMesh* polygon);

	void setMaterial(const MaterialMap& map) { this->materialMaps.push_back(map); }

	Polygon::PolygonMesh* getPolygon() const { return polygon; }

	std::vector<MaterialMap> getMaterialMaps() const { return materialMaps; }

private:
	Polygon::PolygonMesh* polygon;
	std::vector<MaterialMap> materialMaps;
};
	}
}

#endif