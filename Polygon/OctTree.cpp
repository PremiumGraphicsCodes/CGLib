#include "OctTree.h"
#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

OctTree::OctTree(const Space3d<float>& space) :
	space(space)
{}

std::array< OctTree, 8 > OctTree::createChildren()
{
	const auto& spaces = space.getSubSpaces(2, 2, 2);
	assert(spaces.size() == 8);

	std::array<OctTree, 8> results;
	for (int i = 0; i < 8; ++i) {
		OctTree result(spaces[i]);
		//spaces[i].offset(particle)
		const float offsetLength = particles.front()->getRadius();
		spaces[i].offset( Vector3d<float>(offsetLength, offsetLength, offsetLength ) );
		for (const auto p : particles) {
			if (spaces[i].isInner(p->getPosition())) {
				result.add(p);
			}
		}
	}
	return results;
}

bool OctTree::isEmpty() const
{
	return particles.empty();
}
