#include "IndexedParticle.h"

#include "SPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void IndexedParticle::setGridID(const float effectLength)
{
	const Math::Vector3d<float>& point = particle->getPosition();
	gridID = toGridId(point, effectLength);
}

int IndexedParticle::toIdX(Index3d index)
{
	return (index.getZ() << 20) + (index.getY() << 10) + index.getX();
}


int IndexedParticle::toGridId(const Vector3d<float> pos, const float effectLength)
{
	return toIdX( toIndex(pos, effectLength ) );
}

Index3d IndexedParticle::toIndex(const Vector3d<float> pos, const float effectLength)
{
	const auto ix = static_cast<int>(pos.getX() / effectLength);
	const auto iy = static_cast<int>(pos.getY() / effectLength);
	const auto iz = static_cast<int>(pos.getZ() / effectLength);
	return Index3d(ix, iy, iz);
}

