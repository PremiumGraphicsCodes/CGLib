#include "PolygonObjectBuilder.h"

#include "SpaceHash.h"

#include "MarchingCube.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

MCVolume PolygonObjectBuilder::toVolume(const ParticleObject& particleObject)
{
	const auto dx = particleObject.getParticles().front()->getDiameter();
	const auto dy = dx;
	const auto dz = dx;

	SpaceHash spaceHash(dx);
	const auto& particles = particleObject.getParticles();
	for (const auto& p : particles) {
		spaceHash.add(p);
	}
	const auto& bb = particleObject.getBoundingBox();
	const auto minx = bb.getMinX() + dx * 0.5f;
	const auto miny = bb.getMinY() + dy * 0.5f;
	const auto minz = bb.getMinZ() + dz * 0.5f;
	const auto maxx = bb.getMaxX() - dx * 0.5f;
	const auto maxy = bb.getMaxY() - dy * 0.5f;
	const auto maxz = bb.getMaxZ() - dz * 0.5f;
	 
	Space3d<float> space(particleObject.getBoundingBox().getMin(), particleObject.getBoundingBox().getLength());

	const auto resx = static_cast<int>( (maxx - minx) / dx );
	const auto resy = static_cast<int>( (maxy - miny) / dy );
	const auto resz = static_cast<int>( (maxz - minz) / dz );
	Grid3d<float> grid(resx+1, resy+1, resz+1);

	for (int x = 0; x <= resx; ++x) {
		for (int y = 0; y <= resy; ++y) {
			for (int z = 0; z <= resz; ++z) {
				const auto posx = minx + x * dx;
				const auto posy = miny + y * dy;
				const auto posz = minz + z * dz;
				const auto& neighbors = spaceHash.getNeighbor(Vector3d<float>(posx, posy, posz));
				for (auto n : neighbors) {
					Vector3d<float> p(posx, posy, posz);
					const auto distance = p.getDistance( n->getPosition() );
					const auto value = getPoly6Kernel(distance, dx);
					grid.add(x, y, z, value );
				}
			}
		}
	}
	return MCVolume(space, grid);
}