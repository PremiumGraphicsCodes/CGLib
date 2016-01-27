#include "gtest/gtest.h"
#include "../Graphics/PolygonReduction.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics::Experiment;


TEST(PolygonReductionTest, TestCreateVertex)
{
	TriangleMesh mesh;
	const auto v1 = mesh.createVertex( Vector3d<float>(0, 0, 0) );
	const auto v2 = mesh.createVertex( Vector3d<float>(1, 0, 0) );
	//const auto v3 = mesh.createVertex( Vector3d<float>(0, 1, 0) );
	const auto v4 = mesh.createVertex(Vector3d<float>(0, 0, 0));

	//mesh.createFace({ v1, v2, v3 });
	//mesh.createFace()
	mesh.removeOverlappedVerticies();

	EXPECT_EQ(2, mesh.getVertices().size());
}