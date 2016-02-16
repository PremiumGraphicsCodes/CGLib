#include "ActorObject.h"
#include "Particle.h"
#include "ParticleObject.h"
#include "Joint.h"
#include "Bone.h"
#include "BoneTree.h"
#include "../Math/Line3d.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;




void ActorObject::clear()
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


Joint* ActorObject::createJoint(const Vector3d<float>& pos)
{
	auto j = new Joint(pos);
	joints.push_back(j);
	return j;
}


Bone* ActorObject::createBone(Joint* j1, Joint* j2)
{
	auto b = new Bone(j1, j2);
	bones.push_back(b);
	return b;
}
