#ifndef __CRYSTAL_POLYGON_BONE_H__
#define __CRYSTAL_POLYGON_BONE_H__

#include <vector>
#include "../Math/Vector3d.h"
#include "../Math/Line3d.h"

namespace Crystal {
	namespace Polygon {
		class Joint;
		class Particle;

class Bone
{
public:
	Bone(Joint* origin, Joint* dest, const unsigned int id = -1);

	~Bone();

	void clear();

	Bone* createChild(Joint* childDest);

	std::vector<Bone*> getChildren() const { return children; }

	float getLength() const;

	Math::Line3d<float> toLine() const;

	std::vector<Particle> toParticles(const float divideLength, const float density);

	Joint* getOriginJoint() const { return origin; }

	Joint* getDestJoint() const { return dest; }

	std::string getName() const { return "Test";  }

	unsigned int getId() const { return id; }

	bool isTail() const { return origin == nullptr || dest == nullptr; }

	//std::string getName() const { return name; }

private:
	Joint* origin;
	Joint* dest;
	//Bone* parent;
	std::string name;
	std::vector<Bone*> children;
	const unsigned int id;
};

	}
}

#endif