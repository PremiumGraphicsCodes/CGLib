#ifndef __CRYSTAL_CORE_CIRCLE_ARROW_H__
#define __CRYSTAL_CORE_CIRCLE_ARROW_H__

#include "../Math/Vector3d.h"
#include "../Math/CircularCurve3d.h"
#include "../Math/Circle3d.h"
#include "../Math/Cylinder.h"

namespace Crystal {
	namespace Core {
		class Cylinder;

class CircleArrow
{
public:
	CircleArrow(const Math::Circle3d<float>& circle);

private:
	std::vector<Math::Point3d<float>> points;
};
	}
}

#endif