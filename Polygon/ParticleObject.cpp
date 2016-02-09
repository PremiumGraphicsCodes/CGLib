#include "ParticleObject.h"
#include "Particle.h"

#include "../Math/Sphere.h"

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

namespace {
	/*

	int toHash(const Vector3d<float>& pos)
	{
		const int p1 = 73856093;
		const int p2 = 19349663;
		const int p3 = 83492791;
		const int hashTableSize = 10000;
		const int x = static_cast<int>(pos.getX() * p1);
		const int y = static_cast<int>(pos.getY() * p2);
		const int z = static_cast<int>(pos.getZ() * p3);
		return  (x^y^z) % hashTableSize;
	}

	bool comp(Particle* v1, Particle* v2)
	{
		return toHash(v1->getPosition()->getVector()) < toHash(v2->getPosition()->getVector());
	}

	bool isSame(Vertex* v1, Vertex* v2)
	{
		if (v1->position == v2->position) {
			return true;
		}
		return false;
	}
	*/
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

namespace {

	float getPoly6Kernel(const float distance, const float effectLength) {
		assert(distance < effectLength);
		const auto poly6Constant = 315.0f / (64.0f * Tolerance<float>::getPI() * pow(effectLength, 9));
		const auto result = poly6Constant * pow(effectLength * effectLength - distance * distance, 3);
		assert(result > 0.0);
		return result;
	}
}



MCVolume ParticleObject::toVolume(const int hashTableSize) const
{
	auto bb = this->getBoundingBox();

	const auto effectLength = this->getParticles().front()->getDiameter();
	const auto dx = effectLength;

	SpaceHash spaceHash(effectLength, hashTableSize);
	const auto& particles = this->getParticles();
	for (const auto& p : particles) {
		spaceHash.add(p);
	}

	//bb.innerOffset(particles[0]->getRadius());
	Space3d<float> space(bb.getStart(), bb.getLength());

	int resx = static_cast<int>( bb.getLength().getX() / dx );
	int resy = static_cast<int>( bb.getLength().getY() / dx );
	int resz = static_cast<int>( bb.getLength().getZ() / dx );

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
					const auto distance = p.getDistance(n->getPosition());
					const auto v = n->getDensity();
					const auto value = getPoly6Kernel(distance, effectLength) * v;
					grid.add(i, j, k, value);
				}
			}
		}
	}
	return MCVolume(space, grid);
}


