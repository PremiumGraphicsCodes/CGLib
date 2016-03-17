#ifndef __CRYSTAL_POLYGON_OCT_TREE_H__
#define __CRYSTAL_POLYGON_OCT_TREE_H__

#include <array>
#include <vector>

#include "../Math/Space3d.h"
#include "../Math/Box.h"

namespace Crystal {
	namespace Polygon {
		class Particle;

class OctTree
{
public:
	OctTree() {};

	OctTree(const Math::Space3d<float>& space);
	
	void add(Particle* particle) { this->particles.push_back(particle); }

	bool isNeighbor(Particle* particle) const;

	std::vector<OctTree> createChildren() const;

	std::vector<OctTree> createChildren(const Math::Vector3d<float>& length) const;

	std::vector<OctTree> createChildren(const int depth) const;

	bool isEmpty() const;

	bool equals(const OctTree& rhs) const;

	bool operator==(const OctTree& rhs) const;

	bool operator!=(const OctTree& rhs) const;

	Math::Box<float> getBoundingBox() const;

	std::vector<Particle*> getParticles() const { return particles; }

	float getVolume() const;

	float getMass() const;

	float getDensity() const;

private:
	std::vector<Particle*> particles;
	Math::Space3d<float> space;
};

	}
}

#endif