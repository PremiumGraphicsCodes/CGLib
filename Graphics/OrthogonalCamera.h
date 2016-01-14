#ifndef __CRYSTAL_GRAPHICS_ORTHOGONAL_CAMERA_H__
#define __CRYSTAL_GRAPHICS_ORTHOGONAL_CAMERA_H__

#include "ICamera.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class OrthogonalCamera : public ICamera<T>
{
public:
	OrthogonalCamera() {
		init();
	}

	void init();

	Math::Matrix4d<T> getProjectionMatrix() const override;

	void setRect(const T left, const T right, const T bottom, const T top) {
		this->left = left;
		this->right = right;
		this->bottom = bottom;
		this->top = top;
	}

private:
	T left;
	T right;
	T bottom;
	T top;

};

	}
}

#endif