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
	Bone(Joint* origin, Joint* dest);

	~Bone();

	void clear();

	Bone* createChild(Joint* childDest);

	std::vector<Bone*> getChildren() const { return children; }

	float getLength() const;

	Math::Line3d<float> toLine() const;

	std::vector<Particle> toParticles(const float divideLength);

	Joint* getOriginJoint() const { return origin; }

	Joint* getDestJoint() const { return dest; }

	std::string getName() const { return "Test";  }

private:
	Joint* origin;
	Joint* dest;
	//Bone* parent;
	std::vector<Bone*> children;
};

	}
}

#endif