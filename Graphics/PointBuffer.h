#ifndef __CRYSTAL_GRAPHICS_POINT_BUFFER_H__
#define __CRYSTAL_GRAPHICS_POINT_BUFFER_H__

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"
#include "DrawableID.h"


namespace Crystal {
	namespace Physics {
		class SPHParticle;
		class PhysicsObject;
	}
	namespace Polygon {
		class PointObject;
		class PolygonMesh;
		class Particle;
		class ParticleObject;
		class Volume;
		class Actor;
		class Joint;
		class Vertex;
	}
	namespace Graphics {

class Point
{
public:
	Point(const Math::Vector3d<float>& position, const ColorRGBA<float>& color, const float size, const int id = -1) :
		position(position),
		color(color),
		size(size)
	{
		idColor = DrawableID(id).toColor();
	}

	Point(const Polygon::Vertex& vertex);

	Point(const Polygon::Particle& particle);

	Point(const Physics::SPHParticle& particle);

	Math::Vector3d<float> getPosition() const { return position; }

	ColorRGBA<float> getColor() const { return color; }

	ColorRGBA<float> getIdColor() const { return idColor; }

	float getSize() const { return size; }

private:
	Math::Vector3d<float> position;
	ColorRGBA<float> color;
	ColorRGBA<float> idColor;
	float size;
};

class PointBuffer
{
public:
	PointBuffer() {};

	void clear();

	void add(const Point& point);

	void add(const Polygon::PolygonMesh& polygon);

	void add(const Polygon::Volume& volume);

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Graphics::Buffer4d<float> getColor() const { return color; }

	Graphics::Buffer4d<float> getIdColor() const { return idColor; }

	Graphics::Buffer1d<float> getSize() const { return sizes; }
	
private:
	Graphics::Buffer3d<float> position;
	Graphics::Buffer4d<float> color;
	Graphics::Buffer4d<float> idColor;
	Graphics::Buffer1d<float> sizes;
};

	}
}

#endif