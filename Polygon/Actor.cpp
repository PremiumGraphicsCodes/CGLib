#include "Actor.h"
#include "Particle.h"
#include "ParticleObject.h"
#include "Joint.h"
#include "Bone.h"
#include "BoneTree.h"
#include "../Math/Line3d.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;



Actor::Actor()
{}


void Actor::clear()
{
	for (auto b : bones) {
		delete b;
	}
	bones.clear();
	for (auto j : joints) {
		delete j;
	}
	joints.clear();
}


Joint* Actor::createJoint(const Vector3d<float>& pos)
{
	auto j = new Joint(pos, joints.size());
	joints.push_back(j);
	return j;
}

Joint* Actor::insertJoint(Bone* bone)
{
	auto j1 = bone->getOriginJoint();
	auto j2 = bone->getDestJoint();
	const auto& pos = j1->getPosition() / 2.0 + j2->getPosition() / 2.0;
	auto j = createJoint(pos);
	bones.remove(bone);
	auto b1 = createBone(j1, j);
	auto b2 = createBone(j, j2);
	return j;
}



Bone* Actor::createBone(Joint* j1, Joint* j2)
{
	auto b = new Bone(j1, j2, bones.size());
	bones.push_back(b);
	return b;
}

ParticleObject* Actor::toParticleObject(const float radius, const float density) const
{
	//rootBone->getOriginJoint();
	//auto children =
	std::vector<Particle*> particles;
	for (auto b : bones) {
		if (b->isTail()) {
			continue;
		}
		const auto& ps = b->toParticles(radius * 2.0f, density);
		for (const auto& p : ps) {
			particles.push_back( p.clone() );
		}
	}
	return new ParticleObject( particles );
}

Joint* Actor::findJointById(const unsigned int id) const
{
	for (auto j : joints) {
		if (j->getId() == id) {
			return j;
		}
	}
	return nullptr;
}

Bone* Actor::findBoneById(const unsigned int id) const
{
	for (auto b : bones) {
		if (b->getId() == id) {
			return b;
		}
	}
	return nullptr;
}
