#include "gtest/gtest.h"
 
#include "../Graphics/ICamera.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

using T = float;

template<typename T>
class ConcreteCamera : public ICamera<T>
{
public:
	Matrix4d<T> getProjectionMatrix() const {
		return Matrix4d<T>();
	}

};

TEST( ICameraTest, TestMove )
{
	ConcreteCamera<T> c;
	c.move(Vector3d<T>(1.0f, 0.0f, 0.0f));

	EXPECT_EQ(Vector3d<T>(1.0f, 0.0f, 0.0f), c.getPos() );
}

TEST( ICameraTest, TestGetRotationMatrix)
{
	ConcreteCamera<T> c;
	const auto& expected = Matrix3d<T>::Identity();
	const auto& actual = c.getRotationMatrix();
	EXPECT_EQ(expected, actual);
}


