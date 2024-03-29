#ifndef __CRYSTAL_PHYSICS_BULLET_CONVERTER_H__
#define __CRYSTAL_PHYSICS_BULLET_CONVERTER_H__

#include "../Math/Vector3d.h"
#include "../Math/Quaternion.h"
#include "../Math/Matrix4d.h"

#include "Bullet.h"

namespace Crystal {
	namespace Physics {

class BulletConverter
{
public:

	static btVector3 convert(const Math::Vector3d<float>& src);

	static Math::Vector3d<float> convert(const btVector3& src);

	static Math::Quaternion<float> convert(const btQuaternion& src);

	static btQuaternion convert(const Math::Quaternion<float>& src);

	static Math::Matrix4d<float> convert(const btTransform& src);
};

	}
}

#endif