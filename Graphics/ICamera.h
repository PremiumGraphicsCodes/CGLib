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
	ICamera();

	virtual ~ICamera() = default;

	void setCameraXY() { pos = Math::Vector3d<T>(0.0, 0.0, 1.0); }

	void setCameraYZ() { pos = Math::Vector3d<T>(1.0, 0.0, 0.0); }

	void setCameraZX() { pos = Math::Vector3d<T>(0.0, 1.0, 0.0); }

	void moveLookatTo(const Math::Vector3d<T>& p) { this->lookat = p; }

	void move(const Math::Vector3d<T>& move) {
		this->pos += move;
		//this->lookat += move;
	}

	void translate(const Math::Vector3d<T>& v) {
		this->pos += v;
		this->lookat += v;
	}

	void moveTo(const Math::Vector3d<T>& p) { this->pos = p; }

	Math::Vector3d<T> getPosition() const { return pos; }

	Math::Matrix3d<T> getRotationMatrix() const;

	Math::Matrix4d<T> getModelviewMatrix() const;

	void setFar(const T f) { this->far_ = f; }

	void setNear(const T n) { this->near_ = n; }

 
	T getFar() const { return far_; }

	T getNear() const { return near_; }

	T getDistance(const T depth) const;

	virtual Math::Matrix4d<T> getProjectionMatrix() const = 0;

	Math::Vector3d<T> getForwardVector() const;

	Math::Vector3d<T> getUpVector() const;

	Math::Vector3d<T> getRightVector() const;

	void setUpVector(const Math::Vector3d<T>& v) { this->up = v; }

	Math::Matrix4d<T> getBillboardMatrix() const;

	//Math::Ray3d<T> getRay(const T x, const T y) const;

protected:
	Math::Vector3d<T> pos;
	Math::Vector3d<T> up;
	Math::Vector3d<T> lookat;
	T near_;
	T far_;
	T left;
	T right;
	T bottom;
	T top;

};



	}
}

#endif