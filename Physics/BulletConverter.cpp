#include "BulletConverter.h"


using namespace Crystal::Math;
using namespace Crystal::Physics;

btVector3 BulletConverter::convert(const Vector3d<float>& src)
{
	return btVector3(src.getX(), src.getY(), src.getZ());
}

Vector3d<float> BulletConverter::convert(const btVector3& src)
{
	return Vector3d<float>(src.getX(), src.getY(), src.getZ());
}

Quaternion<float> BulletConverter::convert(const btQuaternion& src)
{
	return Quaternion<float>(src.getX(), src.getY(), src.getZ(), src.getW());
}

Matrix4d<float> BulletConverter::convert(const btTransform& src)
{
	std::array<btScalar,16> m;
	src.getOpenGLMatrix(m.data());
	return Matrix4d<float>(
		m[0], m[1], m[2], m[3],
		m[4], m[5], m[6], m[7],
		m[8], m[9], m[10], m[11],
		m[12], m[13], m[14], m[15]
		);
}

