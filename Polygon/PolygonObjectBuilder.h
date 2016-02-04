#ifndef __CRYSTAL_POLYGON_POLYGON_OBJECT_BUILDER_H__
#define __CRYSTAL_POLYGON_POLYGON_OBJECT_BUILDER_H__

#include "../Math/Box.h"
#include "../Math/Sphere.h"

namespace Crystal {
	namespace Polygon {

class PolygonObject;

class PolygonObjectBuilder
{
public:
	PolygonObject* build(const Math::Box<float>& box);

	//PolygonObject* build(const Math::Sphere<float>& sphere);
private:

};
	}
}

#endif
