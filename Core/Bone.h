#ifndef __CRYSTAL_POLYGON_BONE_H__
#define __CRYSTAL_POLYGON_BONE_H__

#include <vector>
#include "UID.h"
#include "stdafx.h"

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
	Bone(Joint* origin, Joint* dest, const Math::Vector2d<float>& thickness, const unsigned int id);

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

	AnisotoropicParticle toAnisoParticles(const float density);

	Math::Ellipsoid<float> toEllipsoid() const;

	Math::Cylindroid<float> toCylindroid() const;

	Math::PolarCoord3d<float> getPolarCoord() const;

	Math::Quaternion<float> getOrientation() const;

	Joint* getOriginJoint() const { return origin; }

	Joint* getDestJoint() const { return dest; }

	std::string getName() const { return "Test";  }

	unsigned int getId() const { return id; }

	bool isRoot() const { return origin == nullptr; }

	bool isTail() const { return origin == nullptr || dest == nullptr; }

	void scale(const Math::Vector2d<float>& dt) { this->thickness += dt; }

	void move(const Math::Vector3d<float>& v);
	//std::string getName() const { return name; }

	Math::Vector2d<float> getThickness() const { return thickness; }

	void setThickness(const Math::Vector2d<float>& v) { this->thickness = v; }

	Math::Angle<float> getRotation() const { return rotation; }

	void setRotation(const Math::Angle<float>& r) { this->rotation = r; }

	void rotate(const Math::Angle<float>& r) { this->rotation += r; }

	Math::Vector3d<float> getCenter() const;


private:
	Joint* origin;
	Joint* dest;
	//Bone* parent;
	std::string name;
	std::vector<Bone*> children;
	Math::Vector2d<float> thickness;
	Math::Angle<float> rotation;
	unsigned int id;
};

	}
}

#endif