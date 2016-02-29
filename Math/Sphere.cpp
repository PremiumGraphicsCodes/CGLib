#include "Sphere.h"

#include "Box.h"

using namespace Crystal::Math;

template<typename T>
Sphere<T>::Sphere() :
	center(Vector3d<T>::Zero()),
	radius(1.0f)
{}

template<typename T>
Sphere<T>::Sphere(const Vector3d<T>& center, const float radius) :
	center(center),
	radius(radius)
{}

template<typename T>
Sphere<T>::Sphere(const Box<T>& boundingBox)
{
	center = Vector3d<T>(boundingBox.getCenter().getX(), boundingBox.getCenter().getY(), boundingBox.getCenter().getZ());
	const Vector3d<T>& length = boundingBox.getLength();
	radius = std::min<float>(std::min<float>(length.getX(), length.getY()), length.getZ()) * 0.5f;
}

template<typename T>
Box<T> Sphere<T>::getBoundingBox() const {
	Math::Box<T> box(center, center);
	return box.getOuterOffset(radius);
}

template<typename T>
Vector3dVector<T> Sphere<T>::toPoints(const float divideLength) const
{
	Vector3dVector<T> points;

	Math::Box<T> box(center, center);
	box.outerOffset(radius);

	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d<T> pos(x, y, z);
				if (pos.getDistanceSquared(center) < radius * radius) {
					points.push_back(pos);
				}
			}
		}
	}
	return points;
}


template class Sphere<float>;
template class Sphere<double>;