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
