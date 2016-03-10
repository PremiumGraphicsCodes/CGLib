#include "Surfels.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

Surfels::Surfels(const Box<float>& box, const float divideLength)
{
	const auto minx = box.getMinX();
	const auto miny = box.getMinY();
	const auto minz = box.getMinZ();
	const auto maxx = box.getMaxX();
	const auto maxy = box.getMaxY();
	const auto maxz = box.getMaxZ();
	for (auto y = miny; y < maxy; y += divideLength) {
		for (auto z = minz; z < maxz; z += divideLength) {
			positions.push_back(Vector3d<float>(minx, y, z));
			positions.push_back(Vector3d<float>(maxx, y, z));
		}
	}
	for (auto x = minx; x < maxx; x += divideLength) {
		for (auto y = miny; y < maxy; y += divideLength) {
			positions.push_back(Vector3d<float>(x, y, minz));
			positions.push_back(Vector3d<float>(x, y, maxz));
		}
	}
	for (auto x = minx; x < maxx; x += divideLength) {
		for (auto z = miny; z < maxz; z += divideLength) {
			positions.push_back(Vector3d<float>(x, miny, z));
			positions.push_back(Vector3d<float>(x, maxy, z));
		}
	}
}

std::vector<Vector3d<float>> Surfels::getWorld(const Vector3d<float>& center, const Quaternion<float>& rotation) const
{
	std::vector<Vector3d<float>> result;
	const auto& matrix = rotation.toMatrix();
	for (const auto& p : positions) {
		auto pos = p * matrix;
		pos += center;
	}
	return result;
}
