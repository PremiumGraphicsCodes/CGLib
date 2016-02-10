#include "VolumeObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

VolumeNode::VolumeNode() :
	pos(Vector3d<float>(0, 0, 0)),
	value(0)
{}

VolumeNode::VolumeNode(const Vector3d<float>& p, const float& v) :
	pos(p),
	value(v)
{}

Vector3d<float> VolumeNode::getInterpolatedPosition(const float v, const VolumeNode& rhs) const
{
	const float scale = static_cast<float> (v - this->value) / static_cast<float>(rhs.value - this->value);
	return this->pos + scale * (rhs.pos - this->pos);
}

namespace {
	Vector3d<float> getUnitLengths(const Space3d<float>& space, const Index3d res)
	{
		const auto x = space.getLengths().getX() / res[0];
		const auto y = space.getLengths().getY() / res[1];
		const auto z = space.getLengths().getZ() / res[2];
		return Vector3d<float>(x, y, z);
	}


	VolumeNode toNode(const Space3d<float>& space, const Grid3d<float>& grid, const Index3d index)
	{
		const auto& lengths = getUnitLengths(space, grid.getSizes());
		const auto& innerSpace = space.offset(lengths);

		const auto divx = grid.getSizeX() - 1;
		const auto divy = grid.getSizeY() - 1;
		const auto divz = grid.getSizeZ() - 1;

		const auto v = grid.toArray8(index[0], index[1], index[2]);
		const auto s = space.getSubSpace(index, divx, divy, divz);
		const auto& center = s.getCenter();

		return VolumeNode(center, grid.get(index.getX(), index.getY(), index.getZ()));
	}



}

std::vector<VolumeNode> VolumeObject::toNodes() const
{
	std::vector<VolumeNode> nodes;
	for (int x = 0; x < grid.getSizeX(); ++x) {
		for (int y = 0; y < grid.getSizeY(); ++y) {
			for (int z = 0; z < grid.getSizeZ(); ++z) {
				nodes.push_back(toNode(space, grid, Index3d(x, y, z)));
			}
		}
	}
	return nodes;
}
