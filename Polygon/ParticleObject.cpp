#include "ParticleObject.h"

#include "../Math/Sphere.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;


ParticleObject::ParticleObject(const std::vector<Vector3d<float>>& positions, const float diameter) :
	radius(diameter * 0.5)
{
	for (const auto& p : positions) {
		particles.push_back(new Particle(p, radius));
	}
	sort();
}


ParticleObject::ParticleObject(const Sphere<float>& sphere, const float diameter) :
	radius(diameter * 0.5)
{
	const auto bb = sphere.getBoundingBox();

	for (auto x = bb.getMinX(); x < bb.getMaxX(); x+= diameter) {
		for (auto y = bb.getMinY(); y < bb.getMaxY(); y += diameter) {
			for (auto z = bb.getMinZ(); z < bb.getMaxZ(); z+= diameter) {
				const Vector3d<float> pos(x, y, z);
				if (sphere.isInner(pos)) {
					particles.push_back(new Particle(pos,radius));
				}
			}
		}
	}
	sort();
}

ParticleObject::ParticleObject(const Box<float>& box, const float diameter) :
	radius( diameter * 0.5 )
{
	for (auto x = box.getMinX(); x < box.getMaxX(); x += diameter) {
		for (auto y = box.getMinY(); y < box.getMaxY(); y += diameter) {
			for (auto z = box.getMinZ(); z < box.getMaxZ(); z += diameter) {
				const Vector3d<float> pos(x, y, z);
				particles.push_back(new Particle(pos, radius));
			}
		}
	}
	sort();
}

Box<float> Particle::getBoundingBox() const
{
	const auto minx = position.getX() - radius;
	const auto miny = position.getY() - radius;
	const auto minz = position.getZ() - radius;
	const auto maxx = position.getX() + radius;
	const auto maxy = position.getY() + radius;
	const auto maxz = position.getZ() + radius;
	return Box<float>(Vector3d<float>(minx, miny, minz), Vector3d<float>(maxx, maxy, maxz));
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
	Box<float> b(particles.front()->getPosition());
	for (const auto& p : particles) {
		b.add(p->getPosition());
	}
	b.outerOffset(radius);
	return b;
}

ParticleObject* ParticleObject::createUnion(const ParticleObject& rhs)
{
	const auto& inter = getUnion(rhs);
	std::vector<Particle*> results;
	for (auto i : inter) {
		results.push_back(i->clone());
	}
	return new ParticleObject(results);
}

ParticleObject* ParticleObject::createSub(const ParticleObject& rhs)
{
	const auto& inter = getSub(rhs);
	std::vector<Particle*> results;
	for (auto i : inter) {
		results.push_back(i->clone());
	}
	return new ParticleObject(results);
}


ParticleObject* ParticleObject::createIntersection(const ParticleObject& rhs)
{
	const auto& inter = getIntersection(rhs);
	std::vector<Particle*> results;
	for (auto i : inter) {
		results.push_back(i->clone());
	}
	return new ParticleObject(results);
}


std::vector<Particle*> ParticleObject::getUnion(const ParticleObject& rhs) const
{
	std::vector<Particle*> particles1 = getSub(rhs);
	std::vector<Particle*> particles2 = rhs.getSub(*this);
	std::vector<Particle*> inter = getIntersection(rhs);
	std::copy(particles2.begin(), particles2.end(), std::back_inserter(particles1));
	std::copy(inter.begin(), inter.end(), std::back_inserter(particles1));
	return particles1;

}

std::vector<Particle*> ParticleObject::getSub(const ParticleObject& rhs) const
{
	std::vector<Particle*> results;
	auto inter = getIntersection(rhs);
	//std::sort(particles.begin(), particles.end());
	std::sort(inter.begin(), inter.end());
	std::set_difference(
		particles.begin(), particles.end(),
		inter.begin(), inter.end(),
		std::back_inserter(results)
		);
	return results;
}


std::vector<Particle*> ParticleObject::getIntersection(const ParticleObject& rhs) const
{
	std::vector<Particle*> results;
	const auto& particles1 = this->particles;
	const auto& particles2 = rhs.particles;
	for (auto p1 : particles1) {
		for (auto p2 : particles2) {
			if (p1->getPosition().getDistance(p2->getPosition()) < getDiameter()) {
				results.push_back(p1);
			}
		}
	}
	return results;
}



