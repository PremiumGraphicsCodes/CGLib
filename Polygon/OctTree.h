#ifndef __CRYSTAL_POLYGON_OCT_TREE_H__
#define __CRYSTAL_POLYGON_OCT_TREE_H__

#include <array>
#include <vector>

#include "../Math/Space3d.h"

namespace Crystal {
	namespace Polygon {
		class Particle;

class OctTree
{
public:

	OctTree() {};

	OctTree(const Math::Space3d<float>& space);
	
	void add(Particle* particle) { this->particles.push_back(particle); }

	std::array<OctTree, 8> createChildren();

	bool isEmpty() const;

	bool equals(const OctTree& rhs) const;

	bool operator==(const OctTree& rhs) const;

	bool operator!=(const OctTree& rhs) const;
private:
	std::vector<Particle*> particles;
	Math::Space3d<float> space;
};

	}
}

#endif