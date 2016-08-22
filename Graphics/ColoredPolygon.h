#ifndef __CRYSTAL_COLORED_POLYGON_H__
#define __CRYSTAL_COLORED_POLYGON_H__

namespace Crystal {
	namespace Core {
		class PolygonMesh;
	}
	namespace Graphics {
		class Material;

class ColoredPolygon
{
public:
	ColoredPolygon(Core::PolygonMesh* polygon, Material* material) :
		polygon(polygon),
		material(material)
	{}

	Core::PolygonMesh* getPolygon() const { return polygon; }

	Material* getMaterial() const { return material; }

private:
	Core::PolygonMesh* polygon;
	Material* material;
};
	}
}

#endif