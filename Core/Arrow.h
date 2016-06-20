#ifndef __CRYSTAL_CORE_ARROW_H__
#define __CRYSTAL_CORE_ARROW_H__

#include "../Math/Vector3d.h"
#include "../Math/CircularCurve3d.h"

namespace Crystal {
	namespace Core {

class Arrow
{
public:
	Arrow();

	Math::CircularCurve3d<float> toCirularCurve() const;

private:
	Math::Vector3d<float> scale;
	std::vector<Math::Point3d<float>> points;
};
	}
}

#endif