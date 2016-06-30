#include "Intersection3d.h"
#include "Radian.h"

using namespace Crystal::Math;

template<typename T>
Intersection3d<T>::Intersection3d()
{}

template<typename T>
Intersection3d<T>::Intersection3d(const Line3d<T>& line, const Triangle3d<T>& triangle)
{
	const auto& n = triangle.getNormal();
	const auto d = -n.getInnerProduct(triangle.getv0());
	const auto denom = n.getInnerProduct(line.getVector());

	if (Tolerance<T>::isEqualLoosely(denom)) {
		return;
	}

	const auto param = -(d + n.getInnerProduct(line.getStart())) / denom;
	if (param < 0 || param > 1) {
		return;
	}

	const auto pos = line.getPosition(param);

	Vector3d<T> v1(triangle.getv0(), pos);
	v1.normalize();
	Vector3d<T> v2(triangle.getv1(), pos);
	v2.normalize();
	Vector3d<T> v3(triangle.getv2(), pos);
	v3.normalize();

	const auto a1 = v1.getInnerProduct(v2);
	const auto a2 = v2.getInnerProduct(v3);
	const auto a3 = v3.getInnerProduct(v1);
	const auto angle = Radian<T>( std::acos(a1) + std::acos(a2) + std::acos(a3) );
	if (angle.get() > Tolerance<T>::getTwoPI()) {
		return;
	}
	this->intersections.push_back(pos);
}
