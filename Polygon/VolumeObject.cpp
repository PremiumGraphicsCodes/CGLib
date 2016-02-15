#include "VolumeObject.h"

#include "../Math/Triangle.h"

#include "VolumeCell.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;


namespace {
	Vector3d<float> getUnitLengths(const Space3d<float>& space, const Index3d res)
	{
		const auto x = space.getLengths().getX() / res[0];
		const auto y = space.getLengths().getY() / res[1];
		const auto z = space.getLengths().getZ() / res[2];
		return Vector3d<float>(x, y, z);
	}


	VolumeNode toNode(const Space3d<float>& space, const Grid3d<float>& grid, const Index3d index)
	{
		const auto& lengths = getUnitLengths(space, grid.getSizes());
		const auto& innerSpace = space.offset(lengths);

		const auto divx = grid.getSizeX() - 1;
		const auto divy = grid.getSizeY() - 1;
		const auto divz = grid.getSizeZ() - 1;

		const auto v = grid.toArray8(index[0], index[1], index[2]);
		const auto s = space.getSubSpace(index, divx, divy, divz);
		const auto& center = s.getCenter();

		return VolumeNode(center, grid.get(index.getX(), index.getY(), index.getZ()));
	}



}

std::vector<VolumeNode> VolumeObject::toNodes() const
{
	std::vector<VolumeNode> nodes;
	for (int x = 0; x < grid.getSizeX(); ++x) {
		for (int y = 0; y < grid.getSizeY(); ++y) {
			for (int z = 0; z < grid.getSizeZ(); ++z) {
				nodes.push_back(toNode(space, grid, Index3d(x, y, z)));
			}
		}
	}
	return nodes;
}

#include "PolygonObject.h"

namespace {
	VolumeCell toCell(const Space3d<float>& space, const Grid3d<float>& grid, const Index3d index)
	{
		const auto& lengths = getUnitLengths(space, grid.getSizes());
		const auto& innerSpace = space.offset(lengths);

		const auto divx = grid.getSizeX() - 1;
		const auto divy = grid.getSizeY() - 1;
		const auto divz = grid.getSizeZ() - 1;

		const auto v = grid.toArray8(index[0], index[1], index[2]);
		const auto s = space.getSubSpace(index, divx, divy, divz);

		return VolumeCell(s, v);
	}
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


std::vector< Triangle<float> > VolumeObject::toTriangles(const float isolevel) const
{
	std::vector<Triangle<float>> triangles;
	for (int x = 0; x < grid.getSizeX() - 1; ++x) {
		for (int y = 0; y < grid.getSizeY() - 1; ++y) {
			for (int z = 0; z < grid.getSizeZ() - 1; ++z) {
				if (grid.isBoundary(x, y, z, isolevel)) {
					const auto& cell = ::toCell(space, grid, Index3d{ x, y, z });
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
