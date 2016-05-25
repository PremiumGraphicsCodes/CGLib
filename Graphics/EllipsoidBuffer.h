#ifndef __CRYSTAL_GRAPHICS_ELLIPSOID_BUFFER_H__
#define __CRYSTAL_GRAPHICS_ELLIPSOID_BUFFER_H__

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "Buffer3d.h"
#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class Ellipsoid
{
public:
	Ellipsoid(const Math::Vector3d<float>& position, const ColorRGBA<float>& color, const float size, const Math::Matrix3d<float>& matrix) :
		position(position),
		color(color),
		size(size)
	{
	}

	Math::Vector3d<float> getPosition() const { return position; }

	Math::Matrix3d<float> getMatrix() const { return matrix; }

	ColorRGBA<float> getColor() const { return color; }

	float getSize() const { return size; }

private:
	Math::Vector3d<float> position;
	ColorRGBA<float> color;
	Math::Matrix3d<float> matrix;
	float size;
};

class EllipsoidBuffer
{
	Graphics::Buffer3d<float> position;
	Graphics::Buffer3d<float> size;
	Graphics::Buffer3d<float> matrixRow1;
	Graphics::Buffer3d<float> matrixRow2;
	Graphics::Buffer3d<float> matrixRow3;
};

	}
}

#endif