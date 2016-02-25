#include "gtest\gtest.h"

#include "../Polygon/VolumeNode.h"
#include "../Polygon/VolumeObject.h"
#include "../Polygon/PolygonObject.h"
#include "../Polygon/ParticleObject.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(VolumeObjectTest, TestToNodes)
{
	Space3d<float> space(Vector3d<float>(0, 0, 0), Vector3d<float>(4, 4, 4));
	Grid3d<float> grid(4, 4, 4);
	grid.set(1, 0, 0, 1);
	VolumeObject object(space, grid);
	const auto& actual = object.toNodes();
	EXPECT_EQ(8, actual.size());
}

TEST(VolumeObjectTest, TestToPolygon)
{
	Space3d<float> space(Vector3d<float>(0, 0, 0), Vector3d<float>(4, 4, 4));
	Grid3d<float> grid(4, 4, 4);
	grid.set(1, 0, 0, 1);
	VolumeObject object(space, grid);
	std::unique_ptr<PolygonObject> actual( object.toPolygonObject(0.5f) );
	EXPECT_EQ( 4, actual->getVertices().size() );
}

TEST(VolumeObjectTest, TestToParticleObject)
{
	Space3d<float> space(Vector3d<float>(0, 0, 0), Vector3d<float>(4, 4, 4));
	Grid3d<float> grid(4, 4, 4);
	grid.set(1, 1, 1, 1);
	VolumeObject object(space, grid);
	std::unique_ptr< ParticleObject > actual( object.toParticleObject(0.5f, 0.5f) );
	EXPECT_EQ(1, actual->getParticles().size());
}