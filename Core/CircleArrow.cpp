#include "stdafx.h"
#include "CircleArrow.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

CircleArrow::CircleArrow(const Circle3d<float>& circle, const int divNum)
{
	for (int i = 0; i < divNum; ++i) {
		const auto center = circle.getPosition( Param<float>(i / (float)(divNum)));
		Math::Cylinder<float> cylinder(center, 0.2f, 0.2f);
		cylinders.push_back(cylinder);
	}
}