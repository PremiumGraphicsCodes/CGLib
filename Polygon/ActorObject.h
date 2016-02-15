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
		class BoneTree;

class ActorObject
{
public:
	ActorObject()
	{}

	~ActorObject() {
		clear();
	}

	void clear();

	Joint* createJoint(const Math::Vector3d<float>& pos, const float radius, const float thickness);

	void setRoot(Bone* bone) { this->rootBone = bone; }

	Bone* createBone(Joint* j1, Joint* j2);

	std::list<Bone*> getBones() const { return bones; }

	std::list<Joint*> getJoints() const { return joints; }

	BoneTree toBoneTree();
		

	//ParticleObject toParticleObject();

private:
	Bone* rootBone;
	std::list<Bone*> bones;
	std::list<Joint*> joints;
};
	}
}

#endif