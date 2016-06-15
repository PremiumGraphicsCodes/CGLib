#ifndef __CRYSTAL_POLYGON_BONE_H__
#define __CRYSTAL_POLYGON_BONE_H__

#include <vector>
#include "../Math/Vector3d.h"
#include "../Math/Line3d.h"
#include "../Math/Ellipsoid.h"
#include "../Math/Quaternion.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class Cylindroid;
	}
	namespace Core {
		class Joint;
		class Particle;
		class AnisotoropicParticle;

class Bone
{
public:
	Bone(Joint* origin, Joint* dest, const Math::Vector3d<float>& thickness, const unsigned int id);

	~Bone();

	Bone* clone(const unsigned int newId) const;

	void changeId(const unsigned int newId) { this->id = newId; }

	void changeOrigin(Joint* origin) { this->origin = origin; }

	void changeDest(Joint* dest) { this->dest = dest; }

	void clear();

	Bone* createChild(Joint* childDest);

	std::vector<Bone*> getChildren() const { return children; }

	float getLength() const;

	Math::Line3d<float> toLine() const;

	std::vector<AnisotoropicParticle> toAnisoParticles(const float density, const float divideLength);

	std::vector< Math::Ellipsoid<float> > toEllipsoids(const float divideLength) const;

	Math::Cylindroid<float> toCylindroid() const;

	Math::PolarCoord3d<float> getPolarCoord() const;

	Math::Quaternion<float> getOrientation() const;

	Joint* getOriginJoint() const { return origin; }

	Joint* getDestJoint() const { return dest; }

	std::string getName() const { return "Test";  }

	unsigned int getId() const { return id; }

	bool isRoot() const { return origin == nullptr; }

	bool isTail() const { return origin == nullptr || dest == nullptr; }

	void scale(const Math::Vector3d<float>& dt) { this->thickness += dt; }

	void move(const Math::Vector3d<float>& v);
	//std::string getName() const { return name; }

	Math::Vector3d<float> getThickness() const { return thickness; }

	void setThickness(const Math::Vector3d<float>& v) { this->thickness = v; }

private:
	Joint* origin;
	Joint* dest;
	//Bone* parent;
	std::string name;
	std::vector<Bone*> children;
	Math::Vector3d<float> thickness;
	unsigned int id;
};

	}
}

#endif