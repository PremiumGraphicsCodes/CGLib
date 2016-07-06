#ifndef __CRYSTAL_CORE_BOOLEAN_ALGO_H__
#define __CRYSTAL_CORE_BOOLEAN_ALGO_H__

#include "../Math/Intersection3d.h"

namespace Crystal {
	namespace Core {
		class Surface;

class BooleanAlgo
{
public:
	BooleanAlgo(Surface* surface1, Surface* surface2);

	Math::Intersection3d<float> findIntersections();
	
private:
	Surface* surface1;
	Surface* surface2;
	Math::Intersection3d<float> intersection;
};
	}
}

#endif