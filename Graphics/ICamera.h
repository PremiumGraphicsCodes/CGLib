#ifndef __CRYSTAL_GRAPHICS_CAMERA_H__
#define __CRYSTAL_GRAPHICS_CAMERA_H__

#include "../Math/Matrix4d.h"
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Graphics {

template< typename T >
class ICamera
{
public:
	ICamera() = default;

	virtual ~ICamera() = default;

	Math::Vector3d<T> getAngle() const { return angle; }

	void addAngle(const Math::Vector3d<T>& a) { this->angle += a; }

	void setAngle(const Math::Vector3d<T>& a) { this->angle = a; }

	void setCameraXY() { setAngle(Math::Vector3d<T>(0.0, 0.0, 0.0)); }

	void setCameraYZ() { setAngle(Math::Vector3d<T>(Math::Tolerance<T>::getHalfPI(), 0.0, 0.0)); }

	void setCameraZX() { setAngle(Math::Vector3d<T>(0.0, Math::Tolerance<T>::getHalfPI(), 0.0)); }

	void move(const Math::Vector3d<T>& move) { this->pos += move; }

	void moveTo(const Math::Vector3d<T>& p) { this->pos = p; }

	Math::Vector3d<T> getPos() const { return pos; }

	Math::Matrix3d<T> getRotationMatrix() const;

	Math::Matrix4d<T> getModelviewMatrix() const;

	void setFar(const T f) { this->far_ = f; }

	void setNear(const T n) { this->near_ = n; }

 
	T getFar() const { return far_; }

	T getNear() const { return near_; }

	T getDistance(const T depth) const;

	virtual Math::Matrix4d<T> getProjectionMatrix() const = 0;

protected:
	Math::Vector3d<T> pos;
	Math::Vector3d<T> angle;
	T near_;
	T far_;

};



	}
}

#endif