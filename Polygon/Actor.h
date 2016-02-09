#ifndef __CRYSTAL_POLYGON_ACTOR_H__
#define __CRYSTAL_POLYGON_ACTOR_H__

#include <list>

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Polygon {
		class Particle;
		class ParticleObject;
		class Joint;
		class Bone;


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