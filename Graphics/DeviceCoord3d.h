#ifndef __CRYSTAL_GRAPHICS_DEVICE_COORD_3D_H__
#define __CRYSTAL_GRAPHICS_DEVICE_COORD_3D_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class DeviceCoord3d
{
public:
	DeviceCoord3d() :
		coord(Math::Vector3d<T>(0, 0, 0))
	{}

	explicit DeviceCoord3d(const Math::Vector3d<T>& c) :
		coord(c)
	{}

	Math::Vector3d<T> get() const { return coord; }

	void add(const DeviceCoord3d<T>& rhs) {
		this->coord += rhs.coord;
	}

	void setX(const T x) { coord.setX( x ); }

	void setY(const T y) { coord.setY( y ); }

	void setZ(const T z) { coord.setZ( z ); }

	T getX() const { return coord.getZ(); }

	T getY() const { return coord.getY(); }

	T getZ() const { return coord.getZ(); }

private:
	Math::Vector3d<T> coord;
};

template<typename T>
class WorldCoord3d
{

public:

	WorldCoord3d() :
		coord(Math::Vector3d<T>(0, 0, 0))
	{}

	WorldCoord3d(const Math::Vector3d<T>& c) :
		coord(c)
	{}

	//void add(const WorldCoord3d<T>)

	Math::Vector3d<T> get() const { return coord; }

private:
	Math::Vector3d<T> coord;
};
	}
}

#endif