#include "Surfels.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

Surfels::Surfels(const Box3d<float>& box, const float divideLength)
{
	const auto minx = box.getMinX() + divideLength * 0.5f;
	const auto miny = box.getMinY() + divideLength * 0.5f;
	const auto minz = box.getMinZ() + divideLength * 0.5f;
	/*
	const auto maxx = box.getMaxX();
	const auto maxy = box.getMaxY();
	const auto maxz = box.getMaxZ();
	for (auto x = minx; x < maxx; x += divideLength) {
		for (auto y = miny; y < maxy; y += divideLength) {
			for (auto z = minz; z < maxz; z += divideLength) {
				positions.push_back(Vector3d<float>(x, y, z));
			}
		}
	}
	*/
	const auto xsize = static_cast<int>( box.getLength().getX() / divideLength ) - 1;
	const auto ysize = static_cast<int>( box.getLength().getY() / divideLength ) - 1;
	const auto zsize = static_cast<int>( box.getLength().getZ() / divideLength ) - 1;
	for (auto i = 0; i <= xsize; ++i) {
		for (auto j = 0; j <= ysize; ++j) {
			for (auto k = 0; k <= zsize; ++k) {
				bool xisIn = (0 < i && i < xsize);
				bool yisIn = (0 < j && j < ysize);
				bool zisIn = (0 < k && k < zsize);
				if (xisIn && yisIn && zisIn) {
					continue;
				}
				const auto x = minx + i * divideLength;
				const auto y = miny + j * divideLength;
				const auto z = minz + k * divideLength;
				positions.push_back(Vector3d<float>(x, y, z));
			}
		}
	}
}

void Surfels::transform(const Vector3d<float>& center, const Quaternion<float>& rotation)
{
	std::vector<Vector3d<float>> result;
	const auto& matrix = rotation.toMatrix();
	for (auto& p : positions) {
		p = p * matrix;
		p += center;
	}
}
