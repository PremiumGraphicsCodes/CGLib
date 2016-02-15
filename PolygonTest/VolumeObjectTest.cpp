#include "gtest\gtest.h"

#include "../Polygon/VolumeObject.h"
#include "../Polygon/PolygonObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(VolumeObjectTest, TestToPolygon)
{
	Space3d<float> space(Vector3d<float>(0, 0, 0), Vector3d<float>(4, 4, 4));
	Grid3d<float> grid(4, 4, 4);
	grid.set(1, 0, 0, 1);
	VolumeObject object(space, grid);
	auto actual = object.toPolygonObject(0.5f);
	EXPECT_EQ( 4, actual->getVertices().size() );

}