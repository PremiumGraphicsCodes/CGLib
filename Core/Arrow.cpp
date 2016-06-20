#include "stdafx.h"
#include "Arrow.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Arrow::Arrow()
{
	std::vector<Vector3d<float>> positions;

	positions.push_back(Vector3d<float>(-0.5, -0.25, 0.0));
	positions.push_back(Vector3d<float>(0.0, -0.25, 0.0));
	positions.push_back(Vector3d<float>(0.0, -0.5, 0.0));
	positions.push_back(Vector3d<float>(0.5, 0.0, 0.0));
	positions.push_back(Vector3d<float>(0.0, 0.5, 0.0));
	positions.push_back(Vector3d<float>(0.0, 0.25, 0.0));
	positions.push_back(Vector3d<float>(-0.5, 0.25, 0.0));

	for (auto p : positions) {
		points.push_back(Point3d<float>(p));
	}
}

CircularCurve3d<float> Arrow::toCirularCurve() const
{
	Point3d<float> center(Vector3d<float>(0, 0, 0));
	CircularCurve3d<float> c(center, points);
	return c;
}
