#include "OctTree.h"
#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

OctTree::OctTree(const Space3d<float>& space) :
	space(space)
{}

bool OctTree::isNeighbor(Particle* particle) const
{
	const auto offset = particle->getRadius() * 1.25f;
	const auto bb = this->getBoundingBox().getOuterOffset(offset);
	return bb.isInterior(particle->getPosition());
}


std::vector< OctTree > OctTree::createChildren() const
{
	const auto& spaces = this->space.getSubSpaces(2, 2, 2);
	assert(spaces.size() == 8);

	std::vector<OctTree> results;

	for (int i = 0; i < 8; ++i) {
		//OctTree result(spaces[i]);
		//const float effectLength = 1.25f * 0.5f;
		//spaces[i].offset( Vector3d<float>(effectLength, effectLength, effectLength));
		//const auto offsetLength = -particles.front()->getDiameter() * 1.25f;
		//const auto expanded = spaces[i].offset( Vector3d<float>(offsetLength, offsetLength, offsetLength ) );
		OctTree result(spaces[i]);
		for (const auto p : particles) {
			if (result.isNeighbor(p)) {
				result.add(p);
			}
		}
		if (!result.isEmpty()) {
			results.push_back(result);
		}
	}

	return results;
}

std::vector<OctTree> OctTree::createChildren(const Vector3d<float>& length) const
{
	const auto howMany2 = static_cast<int>( space.getLengths().getX() / length.getX());
	const int howMany = std::log2f(howMany2);
	return createChildren(howMany);
}


std::vector<OctTree> OctTree::createChildren(const int depth) const
{
	assert(depth >= 0);

	if (depth == 0) {
		return{ *this };
	}
	if (depth == 1) {
		return createChildren();
	}
	const auto& children = createChildren();
	std::vector<OctTree> results;
	for (const auto& child : children) {
		const auto& rs = child.createChildren(depth-1);
		results.insert(results.end(), rs.begin(), rs.end());
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

Box<float> OctTree::getBoundingBox() const
{
	return Box<float>(space.getStart(), space.getEnd());
}
