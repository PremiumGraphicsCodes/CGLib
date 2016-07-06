#include "stdafx.h"

#include "../Core/Surface.h"
#include "../Core/SurfaceFactory.h"
#include "../Core/BooleanAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(BooleanAlgoTest, TestFindIntersection)
{
	Plane3d<float> plane1(Vector3d<float>(0,0,0), Vector3d<float>(1,0,0), Vector3d<float>(1,1,1));
	Plane3d<float> plane2(Vector3d<float>(0.5,0,0), Vector3d<float>(1, 0, 0), Vector3d<float>(1, 1, 1));


	SurfaceFactory factory;
	auto surface1 = factory.create(plane1.toCurve3d());
	auto surface2 = factory.create(plane2.toCurve3d());
	BooleanAlgo algo(surface1, surface2);
	algo.findIntersections();
}