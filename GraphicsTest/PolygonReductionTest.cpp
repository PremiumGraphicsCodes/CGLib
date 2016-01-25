#include "gtest/gtest.h"
#include "../Graphics/PolygonReduction.h"

using namespace Crystal::Graphics::Experiment;

TEST(PolygonReductionTest, TestCreateVertex)
{
	TriangleMesh mesh;
	mesh.createVertex();
}