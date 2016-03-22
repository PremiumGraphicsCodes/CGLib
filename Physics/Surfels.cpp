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
	for (auto x = minx; x < maxx; x += divideLength) {
		for (auto y = miny; y < maxy; y += divideLength) {
			for (auto z = minz; z < maxz; z += divideLength) {
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
