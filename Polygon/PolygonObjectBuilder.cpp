#include "PolygonObjectBuilder.h"

#include "SpaceHash.h"

#include "MarchingCube.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

MCVolume PolygonObjectBuilder::toVolume(const ParticleObject& particleObject, const Index3d resolution)
{
	const auto& bb = particleObject.getBoundingBox();

	const auto dx = bb.getLength().getX() / resolution.getX();
	const auto dy = bb.getLength().getY() / resolution.getY();
	const auto dz = bb.getLength().getZ() / resolution.getZ();

	const auto effectLength = particleObject.getParticles().front()->getDiameter();
	SpaceHash spaceHash(effectLength);
	const auto& particles = particleObject.getParticles();
	for (const auto& p : particles) {
		spaceHash.add(p);
	}
	 
	Space3d<float> space(bb.getStart(), bb.getLength());
	Grid3d<float> grid(resolution);

	for (int i = 0; i < resolution.getX(); ++i) {
		for (int j = 0; j < resolution.getY(); ++j) {
			for (int k = 0; k < resolution.getZ(); ++k) {
				const auto posx = space.getStart().getX() + i * dx;
				const auto posy = space.getStart().getY() + j * dy;
				const auto posz = space.getStart().getZ() + k * dz;
				const auto& neighbors = spaceHash.getNeighbor(Vector3d<float>(posx, posy, posz));
				for (auto n : neighbors) {
					Vector3d<float> p(posx, posy, posz);
					const auto distance = p.getDistance( n->getPosition() );
					const auto value = getPoly6Kernel(distance, effectLength);
					grid.add(i, j, k, value );
				}
			}
		}
	}
	return MCVolume(space, grid);
}