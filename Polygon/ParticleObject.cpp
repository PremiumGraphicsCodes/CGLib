#include "ParticleObject.h"

#include "../Math/Sphere.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

ParticleObject::ParticleObject(const std::vector<Vector3d<float>>& positions)
{
	for (const auto& p : positions) {
		particles.push_back(new Particle(p));
	}
}


ParticleObject::ParticleObject(const Sphere<float>& sphere)
{
	const auto bb = sphere.getBoundingBox();
	const auto dx = bb.getLength().getX() / 10;
	const auto dy = bb.getLength().getY() / 10;
	const auto dz = bb.getLength().getZ() / 10;

	for (auto x = bb.getMinX(); x < bb.getMaxX(); x+= dx) {
		for (auto y = bb.getMinY(); y < bb.getMaxY(); y += dy) {
			for (auto z = bb.getMinZ(); z < bb.getMaxZ(); z+= dz) {
				const Vector3d<float> pos(x, y, z);
				if (sphere.isInner(pos)) {
					particles.push_back(new Particle(pos));
				}
			}
		}
	}
}

ParticleObject::~ParticleObject()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}


#include "MarchingCube.h"

/*
PolygonObject* ParticleObject::toPolygonObject() const
{
	const auto bb = getBoundingBox();
	const Space3d<float> space(bb.getMin(), bb.getLength());
	MarchingCube mc;
	MCVolume 
	mc.march(space, )
}
*/

Box<float> ParticleObject::getBoundingBox() const
{
	Box<float> b(particles.front()->getPosition());
	for (const auto& p : particles) {
		b.add(p->getPosition());
	}
	return b;
}
