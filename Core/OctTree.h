#ifndef __CRYSTAL_CORE_OCT_TREE_H__
#define __CRYSTAL_CORE_OCT_TREE_H__

#include <array>
#include <vector>

#include "../Math/Space3d.h"
#include "../Math/Box3d.h"

namespace Crystal {
	namespace Core {
		class IParticle;

class OctTree
{
public:
	OctTree() {};

	OctTree(const Math::Space3d<float>& space);
	
	void add(IParticle* particle) { this->particles.push_back(particle); }

	bool isNeighbor(IParticle* particle) const;

	std::vector<OctTree> createChildren() const;

	std::vector<OctTree> createChildren(const int depth) const;

	bool isEmpty() const;

	bool equals(const OctTree& rhs) const;

	bool operator==(const OctTree& rhs) const;

	bool operator!=(const OctTree& rhs) const;

	Math::Box3d<float> getBoundingBox() const;

	std::vector<IParticle*> getParticles() const { return particles; }

	float getVolume() const;

	float getMass() const;

	float getDensity() const;

private:
	std::vector<IParticle*> particles;
	Math::Space3d<float> space;
};

	}
}

#endif