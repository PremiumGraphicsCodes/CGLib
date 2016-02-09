#include "PolygonObjectBuilder.h"

#include "SpaceHash.h"

#include "MarchingCube.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

MCVolume PolygonObjectBuilder::toVolume(const ParticleObject& particleObject, const int hashTableSize)
{
	auto bb = particleObject.getBoundingBox();

	const auto effectLength = particleObject.getParticles().front()->getDiameter();
	const auto dx = effectLength;

	SpaceHash spaceHash(effectLength, hashTableSize);
	const auto& particles = particleObject.getParticles();
	for (const auto& p : particles) {
		spaceHash.add(p);
	}
	 
	//bb.innerOffset(particles[0]->getRadius());
	Space3d<float> space(bb.getStart(), bb.getLength());

	int resx = bb.getLength().getX() / dx;
	int resy = bb.getLength().getY() / dx;
	int resz = bb.getLength().getZ() / dx;

	Index3d resolution(resx, resy, resz);
	Grid3d<float> grid(resolution);

	for (int i = 0; i < resolution.getX(); ++i) {
		for (int j = 0; j < resolution.getY(); ++j) {
			for (int k = 0; k < resolution.getZ(); ++k) {
				const auto posx = space.getStart().getX() + dx * 0.5f + i * dx;
				const auto posy = space.getStart().getY() + dx * 0.5f + j * dx;
				const auto posz = space.getStart().getZ() + dx * 0.5f + k * dx;
				const auto& neighbors = spaceHash.getNeighbor(Vector3d<float>(posx, posy, posz));
				for (auto n : neighbors) {
					Vector3d<float> p(posx, posy, posz);
					const auto distance = p.getDistance( n->getPosition() );
					const auto v = n->getValue();
					const auto value = getPoly6Kernel(distance, effectLength) * v;
					grid.add(i, j, k, value );
				}
			}
		}
	}
	return MCVolume(space, grid);
}

float PolygonObjectBuilder::getPoly6Kernel(const float distance, const float effectLength) {
	assert(distance < effectLength);
	const auto poly6Constant = 315.0f / (64.0f * Tolerance<float>::getPI() * pow(effectLength, 9));
	const auto result = poly6Constant * pow(effectLength * effectLength - distance * distance, 3);
	assert(result > 0.0);
	return result;
}
