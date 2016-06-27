#include "Ellipse3d.h"
#include "PolyLine3d.h"

using namespace Crystal::Math;

template<typename T>
Ellipse3d<T>::Ellipse3d()
{}

template<typename T>
Ellipse3d<T>::Ellipse3d(const Vector3d<T> radii, const Vector3d<T>& center) :
	IPrimitive3d<T>(center),
	radii(radii)
{
}


template<typename T>
Ellipse3d<T>::Ellipse3d(const Vector3d<T> radii, const Vector3d<T>& center, const Quaternion<T>& orientation) :
	radii(radii),
	IPrimitive3d<T>(center, orientation)
{
}

template<typename T>
bool Ellipse3d<T>::equals(const Ellipse3d<T>& rhs) const
{
	return
		radii == rhs.radii &&
		center == rhs.center &&
		orientation == rhs.orientation;
}

template<typename T>
bool Ellipse3d<T>::operator==(const Ellipse3d<T>& rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Ellipse3d<T>::operator!=(const Ellipse3d<T>& rhs) const
{
	return !equals(rhs);
}

template<typename T>
Vector3d<T> Ellipse3d<T>::getPosition(const Angle<T> angle) const
{
	T x = radii.getX() * angle.getCos();
	T y = radii.getY() * angle.getSin();
	T z = 0;
	Vector3d<T> vec(x, y, z);
	const auto& rotation = orientation.toMatrix();
	vec.rotate(rotation.transposed());

	return vec + center;
}

template<typename T>
Vector3d<T> Ellipse3d<T>::getPosition(const Param<T> param) const
{
	return getPosition( param.toAngle() );
}

template<typename T>
Polyline3d<T> Ellipse3d<T>::toPolyline(const int number) const
{	
	Polyline3d<T> polyline;
	for (int i = 0; i < number-1; ++i) {
		polyline.add( getPosition(Param<T>( i / (T)number)));
	}
	return polyline;
}

template class Ellipse3d<float>;
template class Ellipse3d<double>;