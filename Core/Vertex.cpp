#include "stdafx.h"
#include "Vertex.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Vertex::Vertex(const Point3d<float>& point, const unsigned int id) :
	Point3d<float>(point),
	id(id)
{
}


Vertex::Vertex(const Vector3d<float>& position, const unsigned int id) :
	Point3d<float>(position),
	id(id)
{}

Vertex::Vertex(const Vector3d<float>& position, const Vector3d<float>& normal, const unsigned int id) :
	Point3d<float>(position, normal),
	id(id)
{}

Vertex::Vertex(const Vector3d<float>& position, const Vector3d<float>& normal, const Vector2d<float>& texCoord, const unsigned int id) :
	Point3d<float>(position, normal, texCoord),
	id(id)
{}

Vertex* Vertex::clone()
{
	return new Vertex(getPosition(), getNormal(), getParameter(), id);
}
