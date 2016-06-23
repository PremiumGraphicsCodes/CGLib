#include "Cone.h"

#include "Tolerance.h"

using namespace Crystal::Math;

template<typename T>
Cone<T>::Cone() :
	radius(0.5),
	height(1)
{
}

template<typename T>
Cone<T>::Cone(const T radius, const T height) :
	radius(radius),
	height(height)
{}

template<typename T>
Cone<T>::Cone(const T radius, const T height, const Vector3d<T>& center) :
	radius(radius),
	height(height),
	IPrimitive3d<T>(center)
{
}

template<typename T>
Cone<T>::Cone(const T radius, const T height, const Vector3d<T>& center, const Quaternion<T>& orientation) :
	radius(radius),
	height(height),
	IPrimitive3d<T>(center, orientation)
{
}


template<typename T>
T Cone<T>::getVolume() const
{
	return Tolerance<T>::getPI() * radius * radius * height / T{ 3 };
}

template<typename T>
Vector3d<T> Cone<T>::getPosition(const Param<T> u, const Param<T> v) const
{
	return getPosition(u.toAngle(), v);
}

template<typename T>
Vector3d<T> Cone<T>::getPosition(const Angle<T> u, const Param<T> v) const
{
	const auto x = radius * (1-v.get()) * u.getCos();
	const auto y = v.get() * height;
	const auto z = radius * (1-v.get()) * u.getSin();

	Vector3d<T> vec(x, y, z);
	const auto rotation = orientation.toMatrix();
	vec.rotate(rotation.transposed());

	return Vector3d<T>(x, y, z) + Vector3d<T>(0, -height*T{ 0.5 }, 0) + center;
}

template<typename T>
Vector3d<T> Cone<T>::getNormal(const Angle<T> u, const Param<T> v) const
{
	const auto& pos = getPosition(u, v);
	const auto xz = std::sqrt(pos.getX()*pos.getX() + pos.getZ()*pos.getZ());
	const auto x = pos.getX() / xz;
	const auto y = xz / (height - pos.getY());
	const auto z = pos.getZ() / xz;
	return Vector3d<T>(x, y, z).getNormalized();
}



template class Cone<float>;
template class Cone<double>;