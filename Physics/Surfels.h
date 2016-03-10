#ifndef __CRYSTAL_PHYSICS_SURFELS_H__
#define __CRYSTAL_PHYSICS_SURFELS_H__

#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Quaternion.h"

namespace Crystal {
	namespace Physics {

class Surfels
{
public:
	Surfels(const Math::Box<float>& box, const float divideLength);

	//Surfels(const Math::Sphere<float>& sphere, const float divideLength);

	std::vector<Math::Vector3d<float>> getWorld(const Math::Vector3d<float>& center, const Math::Quaternion<float>& rotation) const;

private:
	std::vector<Math::Vector3d<float>> positions;
};

	}
}

#endif
