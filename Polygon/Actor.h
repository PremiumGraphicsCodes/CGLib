#ifndef __CRYSTAL_POLYGON_ACTOR_H__
#define __CRYSTAL_POLYGON_ACTOR_H__

#include <list>

#include "../Math/Vector3d.h"
#include "Bone.h"
#include "Joint.h"

namespace Crystal {
	namespace Polygon {
		class Particle;
		class ParticleObject;
		class BoneTree;

class Actor
{
public:
	Actor();

	~Actor() {
		clear();
	}

	void clear();

	Joint* createJoint(const Math::Vector3d<float>& pos);

	Joint* insertJoint(Bone* bone);

	void setRoot(Bone* bone) { this->rootBone = bone; }

	Bone* getRoot() const { return this->rootBone; }

	Bone* createBone(Joint* j1, Joint* j2);

	std::list<Bone*> getBones() const { return bones; }

	std::list<Joint*> getJoints() const { return joints; }

	BoneTree toBoneTree();
	
	ParticleObject* toParticleObject(const float radius, const float density) const;

	//ParticleObject toParticleObject();

	Joint* findJointById(const unsigned int id) const;

	Bone* findBoneById(const unsigned int id) const;

private:
	Bone* rootBone;
	std::list<Bone*> bones;
	std::list<Joint*> joints;
};
	}
}

#endif