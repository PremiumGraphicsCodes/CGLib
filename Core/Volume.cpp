#include "stdafx.h"
#include "Volume.h"

#include "VolumeNode.h"
#include "VolumeCell.h"
#include "Particle.h"
#include "ParticleObject.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Grid3d<float> Volume::subGrid(const Vector3d<float>& start, const Vector3d<float>& end) const
{
	const auto& unitLength = getUnitLength();
	const auto startx = static_cast<int>( start.getX() / unitLength.getX());
	const auto starty = static_cast<int>( start.getY() / unitLength.getY());
	const auto startz = static_cast<int>( start.getZ() / unitLength.getZ());
	Index3d startIndex(startx, starty, startz);
	const auto endx = static_cast<int>(end.getX() / unitLength.getX());
	const auto endy = static_cast<int>(end.getY() / unitLength.getY());
	const auto endz = static_cast<int>(end.getZ() / unitLength.getZ());
	Index3d endIndex(endx, endy, endz);
	const auto newGrid = grid.subGrid(startIndex, endIndex);
	//space.getSubSpace(Index3d(x, indexy, indexz));
	return newGrid;
}


Vector3d<float> Volume::getUnitLength() const
{
	const auto x = space.getLengths().getX() / grid.getSizeX();
	const auto y = space.getLengths().getY() / grid.getSizeY();
	const auto z = space.getLengths().getZ() / grid.getSizeZ();
	return Vector3d<float>(x, y, z);
}


VolumeNode Volume::toNode(const Index3d index) const
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




std::vector<VolumeNode> Volume::toNodes() const
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

#include "PolygonMesh.h"

VolumeCell Volume::toCell(const Index3d index) const
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

#include "PolygonFactory.h"


Vector3d<float> Volume::toPosition(const Index3d index) const
{
	const auto unitLength = getUnitLength();
	const auto origin = space.getStart();
	const auto x = origin.getX() + unitLength.getX() * index.getX();
	const auto y = origin.getY() + unitLength.getY() * index.getY();
	const auto z = origin.getZ() + unitLength.getZ() * index.getZ();
	return Vector3d<float>(x, y, z);
}


Particle Volume::toParticle(const Index3d index, const float radius) const
{
	const auto position = toPosition(index);
	const auto density = grid.get(index.getX(), index.getY(), index.getZ());
	return Particle(position, density, radius);
}

std::vector<Particle> Volume::toParticles(const float radius, const float isolevel) const
{
	const auto& nodes = toNodes();
	std::vector<Particle> particles;
	for (int x = 0; x < grid.getSizeX(); ++x) {
		for (int y = 0; y < grid.getSizeY(); ++y) {
			for (int z = 0; z < grid.getSizeZ(); ++z) {
				if (grid.get(x, y, z) > isolevel) {
					const auto& p = toParticle(Index3d(x, y, z), radius);
					particles.push_back(p);
				}
			}
		}
	}
	return particles;
}


ParticleObject* Volume::toParticleObject(const float radius,const float isolevel) const
{
	const auto& particles = toParticles(radius, isolevel);
	std::vector<IParticle*> ps;
	for (const auto& p : particles) {
		ps.push_back( p.clone() );
	}
	ParticleObject* particleObject = new ParticleObject(ps);
	return particleObject;
}



std::vector< Triangle3d<float> > Volume::toTriangles(const float isolevel) const
{
	std::vector<Triangle3d<float>> triangles;
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

Volume Volume::getOverlapped(const Volume& rhs) const
{
	Space3d<float> newSpace = space.getOverlapped(rhs.space);
	Vector3d<float> startDiff = newSpace.getStart() - space.getStart();
	Vector3d<float> endDiff = newSpace.getEnd() - newSpace.getStart() + startDiff;
	const auto& grid = subGrid(startDiff, endDiff);
	return Volume(newSpace, grid);
}

bool Volume::equals(const Volume& rhs) const
{
	return
		(space == rhs.space) &&
		(grid == rhs.grid);
}

bool Volume::operator==(const Volume& rhs) const
{
	return equals(rhs);
}

bool Volume::operator!=(const Volume& rhs) const
{
	return !equals(rhs);
}


/*
ParticleObject* VolumeObject::toParticleObject() const
{
	ParticleObject* object = new ParticleObject();
	for( n : nodes)
	object->add()
}
*/
