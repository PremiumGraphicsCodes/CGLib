#ifndef __CRYSTAL_GRAPHICS_ELLIPSOID_BUFFER_H__
#define __CRYSTAL_GRAPHICS_ELLIPSOID_BUFFER_H__

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "Buffer1d.h"
#include "Buffer3d.h"
#include "Buffer4d.h"
#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class Ellipsoid
{
public:
	Ellipsoid(const Math::Vector3d<float>& position,const float size, const Math::Matrix3d<float>& matrix, const ColorRGBA<float>& color) :
		position(position),
		size(size),
		matrix(matrix),
		color(color)
	{
	}

	Math::Vector3d<float> getPosition() const { return position; }

	Math::Matrix3d<float> getMatrix() const { return matrix; }

	float getSize() const { return size; }

	ColorRGBA<float> getColor() const { return color; }

private:
	Math::Vector3d<float> position;
	Math::Matrix3d<float> matrix;
	float size;
	ColorRGBA<float> color;
};

class EllipsoidBuffer
{
public:
	void add(const Ellipsoid& e);

	void clear() {
		position.clear();
		size.clear();
		matrixRow1.clear();
		matrixRow2.clear();
		matrixRow3.clear();
		color.clear();
	}

	Graphics::Buffer3d<float> getPosition() const { return position; }
	Graphics::Buffer1d<float> getSize() const { return size; }
	Graphics::Buffer3d<float> getMatrixRow1() const { return matrixRow1; }
	Graphics::Buffer3d<float> getMatrixRow2() const { return matrixRow2; }
	Graphics::Buffer3d<float> getMatrixRow3() const { return matrixRow3; }
	Graphics::Buffer4d<float> getColor() const { return color; }

private:
	Graphics::Buffer3d<float> position;
	Graphics::Buffer1d<float> size;
	Graphics::Buffer3d<float> matrixRow1;
	Graphics::Buffer3d<float> matrixRow2;
	Graphics::Buffer3d<float> matrixRow3;
	Graphics::Buffer4d<float> color;
};

	}
}

#endif