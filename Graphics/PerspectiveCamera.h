#ifndef __CRYSTAL_GRAPHICS_PERSPECTIVE_CAMERA_H__
#define __CRYSTAL_GRAPHICS_PERSPECTIVE_CAMERA_H__

#include "ICamera.h"

namespace Crystal {
	namespace Graphics {

template< typename T >
class PerspectiveCamera : public ICamera<T>
{
public:
	PerspectiveCamera()
	{
		init();
	}

	/*
	PerspectiveCamera(const T near__, const T far__, const T aspect) :
		near_(near__),
		far_(far__),
		aspect(aspect)
	{}
	*/

	void init();

	void setFovy(const T fovy) { this->fovy = fovy; }

	Math::Matrix4d<T> getProjectionMatrix() const override;


private:
	T fovy;
	T aspect;
};

	}
}


#endif