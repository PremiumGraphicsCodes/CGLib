#include "stdafx.h"
#include "../Core/IndexedPolygonSource.h"
#include "../Core/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(IndexedPolygonSourceTest, TestBuild)
{
	std::vector<Vector3d<float>> positions;
	positions.push_back( Vector3d<float>(0, 0, 0) );
	positions.push_back( Vector3d<float>(1, 0, 0) );
	positions.push_back( Vector3d<float>(1, 1, 0));

	Vector3d<float> normal(1, 0, 0);
	Vector2d<float> texCoord(1, 0);
	IndexedPolygonSource source( positions, { normal }, { texCoord } );
	IndexedFace f;
	IndexedVertex v1(0, 0);
	IndexedVertex v2(1, 0);
	IndexedVertex v3(2, 0);
	f.vertices.push_back(v1);
	f.vertices.push_back(v2);
	f.vertices.push_back(v3);
	source.build({ f });
	auto p = source.get();
	EXPECT_EQ(1, p->getFaces().size());
	delete p;
}