#include "stdafx.h"
#include "Arrow.h"
#include "Surface.h"
#include "SurfaceFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Arrow::Arrow(const Vector3d<float>& center)
{
	cone = Cone<float>(1, 1, center + Vector3d<float>(0, 0.5, 0));
	cylinder = Cylinder<float>(center- Vector3d<float>(0,0.5,0), 0.5, 1);
}


Surface* Arrow::toSurface() const
{
	SurfaceFactory factory;
	Surface* surface =  new Surface();
	factory.create( cone.toSideCurve(10) );
	factory.create( cylinder.getSideCurve(10) );
	return surface;
}
