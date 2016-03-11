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



VolumeObject ParticleObject::toVolume(const Box<float>& box, Index3d resolution) const
{
	const auto effectLength = this->getParticles().front()->getDiameter();
	const auto dx = effectLength;

	auto bb = box;
	//bb.outerOffset(effectLength);


	/*
	SpaceHash spaceHash(effectLength, particles.size());
	const auto& particles = this->getParticles();
	for (const auto& p : particles) {
		spaceHash.add(p);
	}
	*/

	bb.outerOffset(dx);
	Space3d<float> space(bb.getStart(), bb.getLength());

	Grid3d<float> grid(resolution.getX()+2, resolution.getY()+2, resolution.getZ()+2);

	for (const auto& p : particles) {
		const auto& position = p->getPosition();
		const auto indexx = position.getX() / dx;
		const auto indexy = position.getY() / dx;
		const auto indexz = position.getZ() / dx;
		for (int i = indexx - 1; i <= indexx + 1; ++i) {
			for (int j = indexy - 1; j <= indexy + 1; ++j) {
				for (int k = indexz - 1; k <= indexz + 1; ++k) {
					const auto posx = /*space.getStart().getX()*/ + dx * 0.5f + i * dx;
					const auto posy = /*space.getStart().getY()*/ + dx * 0.5f + j * dx;
					const auto posz = /*space.getStart().getZ()*/ + dx * 0.5f + k * dx;
					Vector3d<float> nodePosition(posx, posy, posz);

					const auto distanceSquared = position.getDistanceSquared(nodePosition);
					if (distanceSquared < effectLength * effectLength) {
						const auto v = p->getDensity();
						const auto value = getPoly6Kernel(std::sqrt(distanceSquared), effectLength) * v;
						if (grid.isValidIndex(i, j, k)) {
							grid.add(i, j, k, value);
						}
					}
				}
			}
		}
	}
	/*
	for (int i = 0; i < resolution.getX(); ++i) {
		for (int j = 0; j < resolution.getY(); ++j) {
			for (int k = 0; k < resolution.getZ(); ++k) {
				const auto posx = space.getStart().getX() + dx * 0.5f + i * dx;
				const auto posy = space.getStart().getY() + dx * 0.5f + j * dx;
				const auto posz = space.getStart().getZ() + dx * 0.5f + k * dx;
				const auto& neighbors = spaceHash.getNeighbor(Vector3d<float>(posx, posy, posz), effectLength);
				for (auto n : neighbors) {
					Vector3d<float> p(posx, posy, posz);
					const auto distance = p.getDistance(n->getPosition());
					const auto v = n->getDensity();
					const auto value = getPoly6Kernel(distance, effectLength) * v;
					grid.add(i, j, k, value);
				}
			}
		}
	}
	*/
	return VolumeObject(space, grid);
}

PolygonObject* ParticleObject::toPolygon(const float isolevel, const Box<float>& box, Index3d resolution) const
{
	const auto& volume = toVolume(box,resolution);
	return volume.toPolygonObject(isolevel);
}
