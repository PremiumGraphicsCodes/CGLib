#include "VolumeObject.h"

#include "../Math/Triangle.h"

#include "VolumeNode.h"
#include "VolumeCell.h"
#include "Particle.h"
#include "ParticleObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;


Vector3d<float> VolumeObject::getUnitLength() const
{
	const auto x = space.getLengths().getX() / grid.getSizeX();
	const auto y = space.getLengths().getY() / grid.getSizeY();
	const auto z = space.getLengths().getZ() / grid.getSizeZ();
	return Vector3d<float>(x, y, z);
}


VolumeNode VolumeObject::toNode(const Index3d index) const
{
	const auto& lengths = getUnitLength();
	const auto& innerSpace = space.offset(lengths);

	const auto divx = grid.getSizeX() - 1;
	const auto divy = grid.getSizeY() - 1;
	const auto divz = grid.getSizeZ() - 1;

	const auto v = grid.toArray8(index[0], index[1], index[2]);
	const auto s = space.getSubSpace(index, divx, divy, divz);
	const auto& center = s.getCenter();

	return VolumeNode(center, grid.get(index.getX(), index.getY(), index.getZ()));
}




std::vector<VolumeNode> VolumeObject::toNodes() const
{
	std::vector<VolumeNode> nodes;
	for (int x = 1; x < grid.getSizeX()-1; ++x) {
		for (int y = 1; y < grid.getSizeY()-1; ++y) {
			for (int z = 1; z < grid.getSizeZ()-1; ++z) {
				nodes.push_back(toNode(Index3d(x, y, z)));
			}
		}
	}
	return nodes;
}

#include "PolygonObject.h"

VolumeCell VolumeObject::toCell(const Index3d index) const
{
	const auto& lengths = getUnitLength();
	const auto& innerSpace = space.offset(lengths);

	const auto divx = grid.getSizeX() - 1;
	const auto divy = grid.getSizeY() - 1;
	const auto divz = grid.getSizeZ() - 1;

	const auto v = grid.toArray8(index[0], index[1], index[2]);
	const auto s = space.getSubSpace(index, divx, divy, divz);

	return VolumeCell(s, v);
}


PolygonObject* VolumeObject::toPolygonObject(const float isolevel) const
{
	const auto& triangles = toTriangles(isolevel);
	PolygonObject* newMesh = new PolygonObject();
	for (const auto& t : triangles) {
		newMesh->add(t);
	}
	newMesh->removeOverlappedVertices();
	return newMesh;
}

Vector3d<float> VolumeObject::toPosition(const Index3d index) const
{
	const auto unitLength = getUnitLength();
	const auto origin = space.getStart();
	const auto x = origin.getX() + unitLength.getX() * index.getX();
	const auto y = origin.getY() + unitLength.getY() * index.getY();
	const auto z = origin.getZ() + unitLength.getZ() * index.getZ();
	return Vector3d<float>(x, y, z);
}


Particle VolumeObject::toParticle(const Index3d index, const float radius) const
{
	const auto position = toPosition(index);
	const auto density = grid.get(index.getX(), index.getY(), index.getZ());
	return Particle(position, density, radius);
}


ParticleObject* VolumeObject::toParticleObject(const float radius,const float isolevel) const
{
	const auto& nodes = toNodes();
	std::vector<Particle*> particles;
	for (int x = 0; x < grid.getSizeX(); ++x) {
		for (int y = 0; y < grid.getSizeY(); ++y) {
			for (int z = 0; z < grid.getSizeZ(); ++z) {
				if (grid.get(x, y, z) > isolevel) {
					const auto& p = toParticle(Index3d(x, y, z), radius);
					particles.push_back( p.clone() );
				}
			}
		}
	}
	ParticleObject* particleObject = new ParticleObject(particles);
	return particleObject;
}



std::vector< Triangle<float> > VolumeObject::toTriangles(const float isolevel) const
{
	std::vector<Triangle<float>> triangles;
	for (int x = 0; x < grid.getSizeX() - 1; ++x) {
		for (int y = 0; y < grid.getSizeY() - 1; ++y) {
			for (int z = 0; z < grid.getSizeZ() - 1; ++z) {
				if (grid.isBoundary(x, y, z, isolevel)) {
					const auto& cell = toCell(Index3d{ x, y, z });
					const auto& ts = cell.toTriangles(isolevel);
					triangles.insert(triangles.end(), ts.begin(), ts.end());
				}
			}
		}
	}
	return triangles;

}

#include "ParticleObject.h"


/*
ParticleObject* VolumeObject::toParticleObject() const
{
	ParticleObject* object = new ParticleObject();
	for( n : nodes)
	object->add()
}
*/
