#ifndef __CRYSTAL_CORE_ARROW_H__
#define __CRYSTAL_CORE_ARROW_H__

#include "../Math/Vector3d.h"
#include "../Math/CircularCurve3d.h"
#include "../Math/Quaternion.h"

namespace Crystal {
	namespace Core {
		class Surface;

class Arrow
{
public:
	Arrow(const Math::Vector3d<float>& center);

	Math::Cylinder<float> getCylinder() const { return cylinder; }

	Math::Cone<float> getCone() const { return cone; }

	Surface* toSurface() const;

private:
	Math::Cylinder<float> cylinder;
	Math::Cone<float> cone;
};
	}
}

#endif