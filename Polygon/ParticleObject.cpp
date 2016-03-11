#include "ParticleObject.h"
#include "Particle.h"

#include "../Math/Sphere.h"
#include "VolumeObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;



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

void ParticleObject::add(const Box<float>& box, const float diameter, const float charge)
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


Box<float> ParticleObject::getBoundingBox() const
{
	Box<float> b(particles.front()->getBoundingBox());
	for (const auto& p : particles) {
		b.add(p->getBoundingBox());
	}
	return b;
}

#include "SpaceHash.h"

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

#include "../Physics/SPHKernel.h"

namespace {
	Crystal::Physics::SPHKernel<float> kernel;
	float getPoly6Kernel(const float distance, const float effectLength) {
		return kernel.getPoly6Kernel(distance, effectLength);
	}
}



VolumeObject ParticleObject::toVolume(const Box<float>& box, const float effectLength) const
{
	const auto dx = effectLength;

	auto bb = box;
	bb.outerOffset(dx*0.5);

	SpaceHash spaceHash(effectLength, 1000);

	std::vector< std::vector< std::vector<Particle*>>> samplings;
	for (float x = bb.getMinX(); x < bb.getMaxX(); x+=dx/1.0) {
		std::vector<std::vector<Particle*>> ys;
		for (float y = bb.getMinY(); y < bb.getMaxY(); y += dx/1.0) {
			std::vector<Particle*> zs;
			for (float z = bb.getMinZ(); z < bb.getMaxZ(); z += dx/1.0) {
				Particle* p= new Particle(Vector3d<float>(x, y, z), 0.0f, dx * 0.5f);
				zs.push_back(p);
				spaceHash.add(p);
			}
			ys.push_back(zs);
		}
		samplings.push_back(ys);
	}

	Space3d<float> space(bb.getStart(), bb.getLength());

	Grid3d<float> grid(samplings.size(), samplings[0].size(), samplings[0][0].size());

	for (const auto& p : particles) {
		const auto& position = p->getPosition();
		const auto neighborSamples = spaceHash.getNeighbor(position, dx);
		for (auto n : neighborSamples) {
			const auto distance = p->getPosition().getDistance(n->getPosition());
			const auto v = p->getDensity();
			const auto value = getPoly6Kernel(distance, effectLength) * v;
			n->addValue(value);
		}
	}
	for (int i = 0; i < samplings.size(); ++i) {
		for (int j = 0; j < samplings[i].size(); ++j) {
			for (int k = 0; k < samplings[i][j].size(); ++k) {
				grid.set(i, j, k, samplings[i][j][k]->getDensity());
				delete samplings[i][j][k];
			}
		}
	}
	return VolumeObject(space, grid);
}

PolygonObject* ParticleObject::toPolygon(const float isolevel, const Box<float>& box, const float effectLength) const
{
	const auto& volume = toVolume(box,effectLength);
	return volume.toPolygonObject(isolevel);
}
