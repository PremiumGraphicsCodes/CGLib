#include "stdafx.h"
#include "../Core/VolumeNode.h"
#include "../Core/Volume.h"
#include "../Core/PolygonMesh.h"
#include "../Core/ParticleObject.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(VolumeObjectTest, TestSubGrid)
{
	Space3d<float> space(Vector3d<float>(0, 0, 0), Vector3d<float>(4, 4, 4));
	Grid3d<float> grid(4, 4, 4);
	grid.set(3, 3, 3, 1);
	const Volume object(space, grid);
	const auto actual = object.subGrid(Vector3d<float>(2, 2, 2), Vector3d<float>(4,4,4));
	Grid3d<float> expected(2, 2, 2);
	expected.set(1, 1, 1, 1);
	EXPECT_EQ(expected, actual);
}

TEST(VolumeObjectTest, TestGetOverlappedCase1)
{
	const Space3d<float> space1(Vector3d<float>(0, 0, 0), Vector3d<float>(2, 2, 2));
	const Grid3d<float> grid1(2, 2, 2);
	const Volume volume1(space1, grid1);

	const Space3d<float> space2(Vector3d<float>(1, 1, 1), Vector3d<float>(2, 2, 2));
	const Grid3d<float> grid2(2, 2, 2);
	const Volume volume2(space2, grid2);
	const auto& actual = volume1.getOverlapped(volume2);

	const Space3d<float> space3(Vector3d<float>(1, 1, 1), Vector3d<float>(1, 1, 1));
	const Grid3d<float> grid3(1, 1, 1);
	const Volume expected(space3, grid3);
	EXPECT_EQ(expected, actual);
}

TEST(VolumeObjectTest, TestGetOverlappedCase2)
{
	const Space3d<float> space1(Vector3d<float>(0, 0, 0), Vector3d<float>(2, 2, 2));
	const Grid3d<float> grid1(2, 2, 2);
	const Volume volume1(space1, grid1);

	const Space3d<float> space2(Vector3d<float>(-1, -1, -1), Vector3d<float>(2, 2, 2));
	const Grid3d<float> grid2(2, 2, 2);
	const Volume volume2(space2, grid2);
	const auto& actual = volume1.getOverlapped(volume2);

	const Space3d<float> space3(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 1, 1));
	const Grid3d<float> grid3(1, 1, 1);
	const Volume expected(space3, grid3);
	EXPECT_EQ(expected, actual);
}

TEST(VolumeObjectTest, TestGetOverlappedCase3)
{
	const Space3d<float> space1(Vector3d<float>(0, 0, 0), Vector3d<float>(2, 2, 2));
	const Grid3d<float> grid1(2, 2, 2);
	const Volume volume1(space1, grid1);

	const Space3d<float> space2(Vector3d<float>(1, 1, 1), Vector3d<float>(10, 10, 10));
	const Grid3d<float> grid2(2, 2, 2);
	const Volume volume2(space2, grid2);
	const auto& actual = volume1.getOverlapped(volume2);

	const Space3d<float> space3(Vector3d<float>(1, 1, 1), Vector3d<float>(1, 1, 1));
	const Grid3d<float> grid3(1, 1, 1);
	const Volume expected(space3, grid3);
	EXPECT_EQ(expected, actual);
}


TEST(VolumeObjectTest, TestToNodes)
{
	const Space3d<float> space(Vector3d<float>(0, 0, 0), Vector3d<float>(4, 4, 4));
	Grid3d<float> grid(4, 4, 4);
	grid.set(1, 0, 0, 1);
	const Volume object(space, grid);
	const auto& actual = object.toNodes();
	EXPECT_EQ(8, actual.size());
}

TEST(VolumeObjectTest, TestToPolygon)
{
	Space3d<float> space(Vector3d<float>(0, 0, 0), Vector3d<float>(4, 4, 4));
	Grid3d<float> grid(4, 4, 4);
	grid.set(1, 0, 0, 1);
	Volume object(space, grid);
	std::unique_ptr<PolygonMesh> actual( object.toPolygonObject(0.5f) );
	EXPECT_EQ( 4, actual->getVertices().size() );
}

TEST(VolumeObjectTest, TestToParticleObject)
{
	Space3d<float> space(Vector3d<float>(0, 0, 0), Vector3d<float>(4, 4, 4));
	Grid3d<float> grid(4, 4, 4);
	grid.set(1, 1, 1, 1);
	Volume object(space, grid);
	std::unique_ptr< ParticleObject > actual( object.toParticleObject(0.5f, 0.5f) );
	EXPECT_EQ(1, actual->getParticles().size());
}