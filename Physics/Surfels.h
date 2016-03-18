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

	Surfels(const std::vector<Math::Vector3d<float>>& positions) : positions(positions)
	{}

	//Surfels(const Math::Sphere<float>& sphere, const float divideLength);

	void transform(const Math::Vector3d<float>& center, const Math::Quaternion<float>& rotation);

	std::vector<Math::Vector3d<float>> toPositions() const { return positions; }

private:
	std::vector<Math::Vector3d<float>> positions;
};

	}
}

#endif
