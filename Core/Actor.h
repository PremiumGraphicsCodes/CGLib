#ifndef __CRYSTAL_POLYGON_ACTOR_H__
#define __CRYSTAL_POLYGON_ACTOR_H__

#include <list>

#include "../Math/Vector3d.h"
#include "Bone.h"
#include "Joint.h"

namespace Crystal {
	namespace Core {
		class Particle;
		class ParticleObject;
		class BoneTree;

class Actor
{
public:
	Actor();

	explicit Actor(const std::string& name);

	~Actor() {
		clear();
	}

	void clear();

	//Actor* clone();

	void orderIds();

	Joint* createJoint(const Math::Vector3d<float>& pos, const float radius);

	Joint* insertJoint(Bone* bone);

	bool isRoot(Joint* j);

	std::vector<Bone*> getPrevBones(Joint* j);

	std::vector<Bone*> getNextBones(Joint* j);

	void remove(Joint* j);

	void remove(Bone* b);

	void setRoot(Bone* bone) { this->rootBone = bone; }

	Bone* getRoot() const { return this->rootBone; }

	Bone* createBone(Joint* j1, Joint* j2, const Math::Vector2d<float>& thickness);

	std::list<Bone*> getBones() const { return bones; }

	std::list<Joint*> getJoints() const { return joints; }

	BoneTree toBoneTree();
	
	ParticleObject* toParticleObject(const float divideLength, const float density) const;

	//ParticleObject toParticleObject();

	Joint* findJointById(const unsigned int id) const;

	Bone* findBoneById(const unsigned int id) const;

	std::string getName() const { return name; }

	std::vector<OrientedEllipsoid> toEllipsoids(const float divideLength) const;

private:
	std::string name;
	Bone* rootBone;
	std::list<Bone*> bones;
	std::list<Joint*> joints;
	int nextJointId;
	int nextBoneId;
};
	}
}

#endif