#include "Intersection3d.h"
#include "Radian.h"

using namespace Crystal::Math;

template<typename T>
Intersection3d<T>::Intersection3d()
{}

template<typename T>
Intersection3d<T>::Intersection3d(const Line3d<T>& lhs, const Line3d<T>& rhs)
{
	calculate(lhs, rhs);
}


template<typename T>
Intersection3d<T>::Intersection3d(const Line3d<T>& line, const Triangle3d<T>& triangle)
{
	calculate(line, triangle);
}

template<typename T>
Intersection3d<T>::Intersection3d(const Triangle3d<T>& lhs, const Triangle3d<T>& rhs)
{
	calculate(lhs, rhs);
}

template<typename T>
void Intersection3d<T>::calculate(const Line3d<T>& lhs, const Line3d<T>& rhs)
{
	const auto ab = lhs.getVector();
	const auto cd = rhs.getVector();

	const auto n1 = ab.getNormalized();
	const auto n2 = cd.getNormalized();

	const auto work1 = n1.getInnerProduct(n2);
	const auto work2 = 1 - work1 * work1;

	const auto ac = rhs.getStart() - lhs.getStart();

	const auto d1 = (ac.getInnerProduct(n1) - work1 * ac.getInnerProduct(n2)) / work2;

	intersections.push_back( lhs.getStart() + d1 * n1 );
}


template<typename T>
void Intersection3d<T>::calculate(const Line3d<T>& line, const Triangle3d<T>& triangle)
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
	const auto angle = Radian<T>(std::acos(a1) + std::acos(a2) + std::acos(a3));
	if (::fabs(angle.get() - Tolerance<T>::getTwoPI()) > 0) {
		return;
	}
	this->intersections.push_back(pos);

}

template<typename T>
void Intersection3d<T>::calculate(const Triangle3d<T>& lhs, const Triangle3d<T>& rhs)
{
	if (lhs.isSamePlane(rhs)) {
		/*
		Line3d<T> line1(lhs.getv0(), rhs.getv1());
		Line3d<T> line2(lhs.getv1(), rhs.getv2());
		Line3d<T> line3(lhs.getv2(), rhs.getv0());
		calculate(line1, line);
		calculate(line2, line);
		calculate(line3, line);
		*/
	}
	else {
		calculate(lhs, rhs);
	}
}



template class Intersection3d<float>;
template class Intersection3d<double>;
