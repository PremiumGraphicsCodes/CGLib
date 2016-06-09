#include "Quad2d.h"

using namespace Crystal::Math;

template<typename T>
Quad2d<T>::Quad2d(const Vector2d<T>& origin, const Vector2d<T>& length) :
	origin(origin),
	length(length)
{}