#include "BulletConverter.h"


using namespace Crystal::Math;
using namespace Crystal::Physics;

btVector3 Converter::convert(const Vector3d<float>& src)
{
	return btVector3(src.getX(), src.getY(), src.getZ());
}

Vector3d<float> Converter::convert(const btVector3& src)
{
	return Vector3d<float>(src.getX(), src.getY(), src.getZ());
}

Quaternion<float> Converter::convert(const btQuaternion& src)
{
	return Quaternion<float>(src.getX(), src.getY(), src.getZ(), src.getW());
}
