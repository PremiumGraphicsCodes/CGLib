#ifndef __CRYSTAL_GRAPHICS_ELLIPSOID_BUFFER_H__
#define __CRYSTAL_GRAPHICS_ELLIPSOID_BUFFER_H__

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "Buffer1d.h"
#include "Buffer3d.h"
#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class Ellipsoid
{
public:
	Ellipsoid(const Math::Vector3d<float>& position,const float size, const Math::Matrix3d<float>& matrix) :
		position(position),
		size(size),
		matrix(matrix)
	{
	}

	Math::Vector3d<float> getPosition() const { return position; }

	Math::Matrix3d<float> getMatrix() const { return matrix; }

	float getSize() const { return size; }

private:
	Math::Vector3d<float> position;
	Math::Matrix3d<float> matrix;
	float size;
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
	}

	Graphics::Buffer3d<float> getPosition() const { return position; }
	Graphics::Buffer1d<float> getSize() const { return size; }
	Graphics::Buffer3d<float> getMatrixRow1() const { return matrixRow1; }
	Graphics::Buffer3d<float> getMatrixRow2() const { return matrixRow2; }
	Graphics::Buffer3d<float> getMatrixRow3() const { return matrixRow3; }


private:
	Graphics::Buffer3d<float> position;
	Graphics::Buffer1d<float> size;
	Graphics::Buffer3d<float> matrixRow1;
	Graphics::Buffer3d<float> matrixRow2;
	Graphics::Buffer3d<float> matrixRow3;
};

	}
}

#endif