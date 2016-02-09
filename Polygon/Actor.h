#ifndef __CRYSTAL_POLYGON_ACTOR_H__
#define __CRYSTAL_POLYGON_ACTOR_H__

#include <list>

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Polygon {
		class Particle;
		class ParticleObject;
		class Joint;


class Bone
{
public:
	Bone(Joint* origin, Joint* dest);

	std::vector<Math::Vector3d<float>> toPositions(const int howMany) const;

	std::vector<float> toValues(const int howMany) const;

	float getLength() const;

	ParticleObject toParticleObject(const float divideLength);

private:
	Joint* origin;
	Joint* dest;
};

class Actor
{
public:
	Actor()
	{}

	~Actor() {
		clear();
	}

	void clear();

	Joint* createJoint(const Math::Vector3d<float>& pos, const float radius, const float thickness);

	Bone* createBone(Joint* j1, Joint* j2);

	//ParticleObject toParticleObject();

private:
	std::list<Bone*> bones;
	std::list<Joint*> joints;
};
	}
}

#endif