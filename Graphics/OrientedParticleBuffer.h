#ifndef __CRYSTAL_GRAPHICS_ORIENTED_PARTICLE_BUFFER_H__
#define __CRYSTAL_GRAPHICS_ORIENTED_PARTICLE_BUFFER_H__

#include "../Math/Vector3d.h"
#include "../Math/Quaternion.h"
#include "Buffer1d.h"
#include "Buffer2d.h"
#include "Buffer3d.h"
#include "Buffer4d.h"
#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class OrientedParticle
{
public:
	OrientedParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& radii, const Math::Quaternion<float>& orientation, const ColorRGBA<float>& color) :
		position(position),
		radii(radii),
		orientation(orientation),
		color(color)
	{
	}

	Math::Vector3d<float> getPosition() const { return position; }

	Math::Vector3d<float> getRadii() const { return radii; }

	Math::Quaternion<float> getOrientation() const { return orientation; }

	ColorRGBA<float> getColor() const { return color; }

private:
	Math::Vector3d<float> position;
	Math::Vector3d<float> radii;
	Math::Quaternion<float> orientation;
	ColorRGBA<float> color;
};

class OrientedParticleBuffer
{
public:
	void add(const OrientedParticle& e);

	void clear();

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Graphics::Buffer3d<float> getRadii() const { return radii; }

	Graphics::Buffer4d<float> getOrientation() const { return orientation; }

	Graphics::Buffer4d<float> getColor() const { return color; }

	Buffer2d<float> getTexCoord() const { return texCoord; }

	std::vector<unsigned int> getIndices() const { return indices; }

private:
	int nextIndex;
	std::vector<unsigned int> indices;
	Graphics::Buffer3d<float> position;
	Graphics::Buffer2d<float> texCoord;
	Graphics::Buffer3d<float> radii;
	Graphics::Buffer4d<float> orientation;
	Graphics::Buffer4d<float> color;
};

	}
}

#endif