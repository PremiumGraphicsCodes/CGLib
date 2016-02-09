#ifndef __CRYSTAL_POLYGON_ACTOR_H__
#define __CRYSTAL_POLYGON_ACTOR_H__

#include <list>

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Polygon {

class Joint
{
public:
	Joint(const Math::Vector3d<float>& pos) :
		pos(pos)
	{}

private:
	Math::Vector3d<float> pos;
};

class Bone
{
public:
	Bone(Joint* origin, Joint* dest):
		origin( origin ),
		dest( dest )
	{}

	std::vector< Math::Vector3d<float> > toPositions() {

	}

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
		for (auto b : bones) {
			delete b;
		}
		bones.clear();
		for (auto j : joints) {
			delete j;
		}
		joints.clear();
	}

	Joint* createJoint(const Math::Vector3d<float>& pos) {
		auto j = new Joint(pos);
		joints.push_back(j);
		return j;
	}

	Bone* createBone(Joint* j1, Joint* j2) {
		auto b = new Bone(j1, j2);
		bones.push_back(b);
		return b;
	}

private:
	std::list<Bone*> bones;
	std::list<Joint*> joints;
};
	}
}

#endif