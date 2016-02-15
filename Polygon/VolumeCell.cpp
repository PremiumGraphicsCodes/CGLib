#include "VolumeCell.h"
#include "VolumeNode.h"

#include "../Math/Triangle.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

Triangle<float> VolumeCell::toTriangle() const
{
	return Triangle<float>();
}

std::array< VolumeNode, 8 > VolumeCell::toPositionValues() const
{
	std::array< VolumeNode, 8 > pvs;
	const auto& positions = space.toArray();
	for (size_t i = 0; i < 8; ++i) {
		pvs[i] = VolumeNode(positions[i], values[i]);
	}
	return pvs;
}

