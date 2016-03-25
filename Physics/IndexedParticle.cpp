#include "IndexedParticle.h"

#include "SPHParticle.h"

using namespace Crystal::Physics;

void IndexedParticle::setGridID(const float effectLength)
{
	const Math::Vector3d<float>& point = particle->getPosition();
	int gridX = static_cast<int>(point.getX() / effectLength);
	int gridY = static_cast<int>(point.getY() / effectLength);
	int gridZ = static_cast<int>(point.getZ() / effectLength);
	gridID = getID(gridX, gridY, gridZ);
}
