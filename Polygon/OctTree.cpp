#include "OctTree.h"
#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

OctTree::OctTree(const Space3d<float>& space) :
	space(space)
{}

std::vector< OctTree > OctTree::createChildren() const
{
	const auto& spaces = this->space.getSubSpaces(2, 2, 2);
	assert(spaces.size() == 8);

	std::vector<OctTree> results;

	for (int i = 0; i < 8; ++i) {
		OctTree result(spaces[i]);
		//spaces[i].offset(particle)
		const auto offsetLength = -particles.front()->getRadius();
		const auto expanded = spaces[i].offset( Vector3d<float>(offsetLength, offsetLength, offsetLength ) );
		for (const auto p : particles) {
			if (expanded.isInner(p->getPosition())) {
				result.add(p);
			}
		}
		if (!result.isEmpty()) {
			results.push_back(result);
		}
	}

	return results;
}

std::vector<OctTree> OctTree::createChildren(const int depth) const
{
	assert(depth >= 1);

	if (depth == 1) {
		return createChildren();
	}
	const auto& children = createChildren();
	std::vector<OctTree> results;
	for (const auto& child : children) {
		results = child.createChildren(depth-1);
	}
	return results;
}


bool OctTree::isEmpty() const
{
	return particles.empty();
}

bool OctTree::equals(const OctTree& rhs) const
{
	return
		(this->space == rhs.space) &&
		(this->particles == rhs.particles);
}

bool OctTree::operator==(const OctTree& rhs) const
{
	return equals(rhs);
}

bool OctTree::operator!=(const OctTree& rhs) const
{
	return !equals(rhs);
}
