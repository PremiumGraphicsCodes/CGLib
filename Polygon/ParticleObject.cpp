#include "ParticleObject.h"
#include "Particle.h"

#include "../Math/Sphere.h"
#include "VolumeObject.h"
#include "PolygonObject.h"

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

#include "OctTree.h"

VolumeObject* ParticleObject::toVolume(const Box<float>& box, const float effectLength) const
{
	const auto dx = effectLength;
	auto bb = box;
	bb.outerOffset(dx*0.5);

	SpaceHash spaceHash(effectLength, this->particles.size());

	std::vector< std::vector< std::vector<Particle*>>> samplings;
	for (float x = bb.getMinX(); x < bb.getMaxX(); x += dx / 1.0) {
		std::vector<std::vector<Particle*>> ys;
		for (float y = bb.getMinY(); y < bb.getMaxY(); y += dx / 1.0) {
			std::vector<Particle*> zs;
			for (float z = bb.getMinZ(); z < bb.getMaxZ(); z += dx / 1.0) {
				Particle* p = new Particle(Vector3d<float>(x, y, z), 0.0f, dx * 0.5f);
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
	return new VolumeObject(space, grid);
}


std::vector<VolumeObject*> ParticleObject::toVolumes(const float effectLength) const
{
	const auto dx = effectLength;

	Vector3d<float> start(-128.0f, -128.0f, -128.0f);
	Vector3d<float> length(256.0f, 256.0f, 256.0f);
	OctTree tree( Space3d<float>( start, length) );
	for (const auto p : particles) {
		tree.add(p);
	}

	std::vector<OctTree> children = tree.createChildren(Vector3d<float>(16.0f, 16.0f, 16.0f));
	//for (const auto& child : children) {
	std::vector<ParticleObject*> cp;

	for (int i = 0; i < children.size(); ++i) {
		cp.push_back( new ParticleObject(children[i].getParticles()) );
	}
	std::vector<VolumeObject*> results(cp.size());


#ifdef _OPENMP
#pragma omp parallel for
#endif
	for (int i = 0; i < cp.size(); ++i) {
		results[i] = cp[i]->toVolume( children[i].getBoundingBox(), effectLength);
	}
	return results;
}

#include "VolumeCell.h"

PolygonObject* ParticleObject::toPolygon(const float isolevel, const float effectLength) const
{
	/*
	auto v = toVolume(box, effectLength);
	return v.toPolygonObject(isolevel);
*/
	Vector3d<float> start(-128.0f, -128.0f, -128.0f);
	Vector3d<float> length(256.0f, 256.0f, 256.0f);

	OctTree tree(Space3d<float>(start, length));
	for (auto& p : particles) {
		tree.add(p);
	}
	std::vector<VolumeCell> cells;
	const auto& children = tree.createChildren(8);//Vector3d<float>(effectLength,effectLength,effectLength));
	for (const auto& c : children) {
		const auto& box = c.getBoundingBox();
		const auto& poss = box.toSpace().toArray();
		std::array<float, 8> values;
		values.fill(0.0f);
		for (int i = 0; i < 8; ++i) {
			for (const auto& particle : c.getParticles()) {
				const auto dist2 = poss[i].getDistanceSquared(particle->getPosition());
				if (dist2 < effectLength * effectLength) {
					const auto value = kernel.getPoly6Kernel(std::sqrt(dist2), effectLength) * particle->getDensity();
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
	PolygonObject* result = new PolygonObject();
	for (const auto& t : triangles) {
		result->add(t);
	}
	result->removeOverlappedVertices();
	return result;
}

