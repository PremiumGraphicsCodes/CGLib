#include "stdafx.h"
#include "../Core/Face.h"
#include "../Core/Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(FaceTest, Test)
{
	Vertex v1(Vector3d<float>(-1, 0, 0), 0);
	Vertex v2(Vector3d<float>(1, 0, 0), 0);
	Vertex v3(Vector3d<float>(1, 1, 0), 0);

	Face f(&v1, &v2, &v3);
	EXPECT_FLOAT_EQ(1, f.getArea());
}
