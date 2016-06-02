#include "OctTree.h"
#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

OctTree::OctTree(const Space3d<float>& space) :
	space(space)
{}

bool OctTree::isNeighbor(IParticle* particle) const
{
	const auto& position = particle->getPosition();
	const auto bb = particle->getBoundingBox();
	const auto offsetx = bb.getLength().getX() * 0.5f;
	//const auto bb = this->getBoundingBox().getOuterOffset(offset);
	const auto minx = space.getStart().getX() - offsetx;
	const auto maxx = space.getEnd().getX() + offsetx;
	const auto x = position.getX();
	if( x < minx || maxx < x) {
		return false;
	}
	const auto offsety = bb.getLength().getY() * 0.5f;
	const auto miny = space.getStart().getY() - offsety;
	const auto maxy = space.getEnd().getY() + offsety;
	const auto y = position.getY();
	if (y < miny || maxy < y) {
		return false;
	}
	const auto offsetz = bb.getLength().getZ() * 0.5f;
	const auto minz = space.getStart().getZ() - offsetz;
	const auto maxz = space.getEnd().getZ() + offsetz;
	const auto z = position.getZ();
	if (z < minz || maxz < z) {
		return false;
	}
	return true;
}


std::vector< OctTree > OctTree::createChildren() const
{
	const auto& spaces = this->space.getSubSpaces(2, 2, 2);
	assert(spaces.size() == 8);

	std::vector<OctTree> results;

	for (int i = 0; i < 8; ++i) {
		OctTree result(spaces[i]);
		for (const auto p : particles) {
			if (result.isNeighbor(p)) {
				result.add(p);
			}
		}
		if (!result.isEmpty() ) {
			results.push_back(result);
		}
	}

	return std::move(results);
}


std::vector<OctTree> OctTree::createChildren(const int depth) const
{
	assert(depth >= 0);

	if (depth == 0) {
		return{ *this };
	}
	if (depth == 1) {
		return std::move( createChildren() );
	}
	const auto& children = createChildren();
	std::vector<OctTree> results;
	for (const auto& child : children) {
		const auto& rs = child.createChildren(depth-1);
		results.insert(results.end(), rs.begin(), rs.end());
	}
	return std::move(results);
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

Box3d<float> OctTree::getBoundingBox() const
{
	return Box3d<float>(space.getStart(), space.getEnd());
}

float OctTree::getVolume() const
{
	return space.getVolume();
}

float OctTree::getMass() const
{
	return particles.size() * 1.0f;
}

float OctTree::getDensity() const
{
	return getMass() / getVolume();
}
