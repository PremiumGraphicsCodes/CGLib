#include "Actor.h"
#include "Particle.h"
#include "AnisotoropicParticle.h"
#include "ParticleObject.h"
#include "Joint.h"
#include "Bone.h"
#include "BoneTree.h"
#include "../Math/Line3d.h"

using namespace Crystal::Math;
using namespace Crystal::Core;



Actor::Actor() :
	nextBoneId(0),
	nextJointId(0)
{}

Actor::Actor(const std::string& name) :
	name(name),
	nextBoneId(0),
	nextJointId(0)
{
}

bool Actor::isRoot(Joint* j)
{
	return getPrevBones(j).empty();
}

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
	nextBoneId = 0;
	nextJointId = 0;
}

/*
Actor* Actor::clone()
{
	auto newActor = new Actor(name);

	int nextId = 0;
	std::vector< Bone* > newBones;
	for (auto b : bones) {
		//newBones.push_back( b->clone(nextId++) );
		newActor->createBone()
	}
	nextId = 0;
	std::vector< Joint* > newJoints;
	for (auto j : joints) {
		newJoints.push_back( j->clone(nextId++) );
	}
	newActor->bones = bon
	 bones.begin(), bones.end();
}
*/

void Actor::orderIds()
{
	nextBoneId = 0;
	for (auto b : bones) {
		b->changeId(nextBoneId++);
	}
	nextJointId = 0;
	for (auto j : joints) {
		j->changeId(nextJointId++);
	}
}

Joint* Actor::createJoint(const Vector3d<float>& pos, const Vector3d<float>& radii)
{
	auto j = new Joint(pos, radii, nextJointId++);
	joints.push_back(j);
	return j;
}

Joint* Actor::insertJoint(Bone* bone)
{
	auto j1 = bone->getOriginJoint();
	auto j2 = bone->getDestJoint();
	const auto& pos = j1->getPosition() / 2.0f + j2->getPosition() / 2.0f;
	const auto radius = j1->getBoundingRadius() / 2.0f + j2->getBoundingRadius() / 2.0f;
	auto j = createJoint(pos, Vector3d<float>(radius, radius, radius));
	bones.remove(bone);
	auto b1 = createBone(j1, j, Vector3d<float>(radius, radius, radius));
	auto b2 = createBone(j, j2, Vector3d<float>(radius, radius, radius));
	return j;
}



Bone* Actor::createBone(Joint* j1, Joint* j2, const Vector3d<float>& thickness)
{
	auto b = new Bone(j1, j2, thickness, nextBoneId++);
	bones.push_back(b);
	return b;
}

std::vector<Bone*> Actor::getPrevBones(Joint* j)
{
	std::vector<Bone*> prevBones;
	for (auto b : bones) {
		if (b->getDestJoint() == j) {
			prevBones.push_back(b);
		}
	}
	return prevBones;
}

std::vector<Bone*> Actor::getNextBones(Joint* j)
{
	std::vector<Bone*> nextBones;
	for (auto b : bones) {
		if (b->getOriginJoint() == j) {
			nextBones.push_back(b);
		}
	}
	return nextBones;
}


void Actor::remove(Joint* j)
{
	if (isRoot(j)) {
		return;
	}
	const auto& prevBones = getPrevBones(j);
	const auto& nextBones = getNextBones(j);

	for (auto pb : prevBones) {
		for (auto nb : nextBones) {
			nb->changeOrigin(pb->getOriginJoint());
		}
	}
	for (auto pb : prevBones) {
		remove(pb);
	}

	joints.erase(std::remove(joints.begin(), joints.end(), j), joints.end());
	delete j;
}

void Actor::remove(Bone* b)
{
	bones.erase(std::remove(bones.begin(), bones.end(), b), bones.end());
	delete b;
	/*
	b->changeDest();
	Bone* bone = nullptr;
	for (auto b : bones) {
		;
	}
	*/
}

ParticleObject* Actor::toParticleObject(const float density) const
{
	std::vector<IParticle*> particles;
	for (auto j : joints) {
		particles.push_back( j->toParticle(density).clone() );
	}
	for (auto b : bones) {
		if (b->isTail()) {
			continue;
		}
		const auto& ps = b->toAnisoParticles(density);
		for (const auto& p : ps) {
			particles.push_back( p.clone() );
		}
	}
	return new ParticleObject( particles );
}

std::vector<Ellipsoid<float>> Actor::toEllipsoids() const
{
	std::vector<Ellipsoid<float>> ellipsoids;
	for (auto j : joints) {
		const auto e = j->toEllipsoid();
		ellipsoids.push_back(e);
	}
	for (auto b : bones) {
		if (b->isTail()) {
			continue;
		}
		const auto& es = b->toEllipsoids();
		ellipsoids.insert(ellipsoids.end(), es.begin(), es.end());
	}
	return ellipsoids;
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
