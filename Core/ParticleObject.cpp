#include "ParticleObject.h"
#include "Particle.h"

#include "../Math/Sphere.h"
#include "Volume.h"
#include "PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Core;



void ParticleObject::add(const Sphere<float>& sphere, const float diameter, const float charge)
{
	const auto bb = sphere.getBoundingBox();

	for (auto x = bb.getMinX(); x <= bb.getMaxX(); x+= diameter) {
		for (auto y = bb.getMinY(); y <= bb.getMaxY(); y += diameter) {
			for (auto z = bb.getMinZ(); z <= bb.getMaxZ(); z+= diameter) {
				const Vector3d<float> pos(x, y, z);
				if (sphere.isInner(pos)) {
					const auto density = (sphere.getRadius() - sphere.getCenter().getDistance(pos)) * charge;
					particles.push_back(new Particle(pos, density, diameter * 0.5f));
				}
			}
		}
	}
	sort();
}

void ParticleObject::add(const Box3d<float>& box, const float diameter, const float charge)
{
	for (auto x = box.getMinX(); x < box.getMaxX(); x += diameter) {
		for (auto y = box.getMinY(); y < box.getMaxY(); y += diameter) {
			for (auto z = box.getMinZ(); z < box.getMaxZ(); z += diameter) {
				const Vector3d<float> pos(x, y, z);
				particles.push_back(new Particle(pos, 1.0f, diameter * 0.5f));
			}
		}
	}
	sort();
}


void ParticleObject::add(const Particle& particle)
{
	particles.push_back(particle.clone());
	sort();
}

void ParticleObject::add(IParticle* particle)
{
	particles.push_back(particle);
	sort();
}


ParticleObject::~ParticleObject()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

void ParticleObject::sort()
{
	std::sort(particles.begin(), particles.end());
}


Box3d<float> ParticleObject::getBoundingBox() const
{
	Box3d<float> b(particles.front()->getBoundingBox());
	for (const auto& p : particles) {
		b.add(p->getBoundingBox());
	}
	return b;
}

#include "SpaceHash.h"
/*
std::vector<Particle*> ParticleObject::getIntersection(const ParticleObject& rhs) const
{
	SpaceHash spaceHash(this->particles.front()->getDiameter(), 1000);
	for (const auto& p : particles) {
		spaceHash.add(p);
	}

	std::vector<Particle*> results;
	//const auto& particles1 = this->particles;
	const auto& particles2 = rhs.particles;
	for (const auto& p : particles2) {
		const auto ns = spaceHash.getNeighbor(p);
		results.insert(results.end(), ns.begin(), ns.end());
	}
	return results;
}
*/
#include "../Math/SPHKernel.h"

namespace {
	Crystal::Math::SPHKernel<float> kernel;
	float getPoly6Kernel(const float distance, const float effectLength) {
		return kernel.getPoly6Kernel(distance, effectLength);
	}
}

#include "OctTree.h"

#include "VolumeCell.h"

PolygonMesh* ParticleObject::toPolygon(const float isolevel, const int levelOfDetail, const Space3d<float>& space) const
{
	OctTree tree(space);
	for (auto& p : particles) {
		tree.add(p);
	}
	std::vector<VolumeCell> cells;
	const auto& children = tree.createChildren(levelOfDetail);//Vector3d<float>(effectLength,effectLength,effectLength));
	for (const auto& c : children) {
		const auto& box = c.getBoundingBox();
		const auto& poss = box.toSpace().toArray();
		std::array<float, 8> values;
		values.fill(0.0f);
		for (int i = 0; i < 8; ++i) {
			for (const auto& particle : c.getParticles()) {
				const auto dist2 = poss[i].getDistanceSquared(particle->getPosition());
				const auto radiusSquared = particle->getBoundingRadius() * particle->getBoundingRadius();
				if (dist2 < radiusSquared) {
					//const auto value = kernel.getPoly6Kernel(std::sqrt(dist2), std::sqrt(radiusSquared)) * particle->getDensity();
					const auto diff = poss[i] - particle->getPosition();
					const auto& m = particle->getMatrix().getScaled(1.0 / particle->getBoundingRadius());
	//				const auto mm = Matrix3d<float>(1.0 / particle->getRadii().getX(), 0, 0, 0, 1.0 / particle->getRadii().getY(), 0, 0, 0, 1.0 / particle->getRadii().getZ());
					const auto value = kernel.getCubicSpline(diff, m) * particle->getDensity();
					values[i] += value;
				}
			}
		}
		VolumeCell cell(c.getBoundingBox().toSpace(),values);
		cells.emplace_back(cell);
	}
	std::vector<Triangle<float>> triangles;
	for (const auto& cell : cells) {
		const auto& ts = cell.toTriangles(isolevel);
		triangles.insert(triangles.end(), ts.begin(), ts.end());
	}
	PolygonMesh* result = new PolygonMesh();
	for (const auto& t : triangles) {
		result->add(t);
	}
	result->removeOverlappedVertices();
	return result;
}

std::vector<Ellipsoid<float>> ParticleObject::toEllipsoids() const
{
	std::vector<Ellipsoid<float>> ellipsoids;
	for (auto p : particles) {
		Ellipsoid<float> e(p->getPosition(), p->getRadii(), p->getOrientation());
		ellipsoids.push_back(e);
	}
	return ellipsoids;
}
