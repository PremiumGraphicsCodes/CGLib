#include "stdafx.h"
#include "CircleArrow.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

CircleArrow::CircleArrow(const Circle3d<float>& circle)
{
	for (int i = 0; i < 10; ++i) {
		circle.getPosition( Param<float>(i / 10.0f));
	}
}