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
	CircleArrow(const Math::Circle3d<float>& circle,const int divNum);

	std::vector<Math::Cylinder<float>> getCylinders() const { return cylinders; }

private:
	std::vector<Math::Cylinder<float>> cylinders;

};
	}
}

#endif