#ifndef __CRYSTAL_POLYGON_BONE_H__
#define __CRYSTAL_POLYGON_BONE_H__

#include <vector>
#include "../Math/Vector3d.h"
#include "../Math/Line3d.h"

namespace Crystal {
	namespace Polygon {
		class Joint;
		class Particle;

class Bone
{
public:
	Bone(Joint* origin, Joint* dest);

	std::vector<Math::Vector3d<float>> toPositions(const int howMany) const;

	std::vector<float> toValues(const int howMany) const;

	float getLength() const;

	Math::Line3d<float> toLine() const;

	std::vector<Particle> toParticles(const float divideLength);

private:
	Joint* origin;
	Joint* dest;
};

	}
}

#endif