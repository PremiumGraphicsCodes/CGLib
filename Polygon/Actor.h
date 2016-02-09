#ifndef __CRYSTAL_POLYGON_ACTOR_H__
#define __CRYSTAL_POLYGON_ACTOR_H__

#include <list>

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Polygon {

class Joint
{
public:
	Joint(const Math::Vector3d<float>& pos, const float thickness) :
		pos(pos),
		thickness(thickness)
	{}

	Math::Vector3d<float> getPosition() const { return pos; }

private:
	Math::Vector3d<float> pos;
	float thickness;
};

class Bone
{
public:
	Bone(Joint* origin, Joint* dest);

	std::vector< Math::Vector3d<float> > toPositions(const float divideLength);

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

	Joint* createJoint(const Math::Vector3d<float>& pos, const float thickness);

	Bone* createBone(Joint* j1, Joint* j2);

private:
	std::list<Bone*> bones;
	std::list<Joint*> joints;
};
	}
}

#endif