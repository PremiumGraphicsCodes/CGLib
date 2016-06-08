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

	EXPECT_EQ(Vector3d<T>(1.0f, 0.0f, 0.0f), c.getPosition() );
}

TEST( ICameraTest, TestGetRotationMatrixXY)
{
	ConcreteCamera<T> c;
	c.move(Vector3d<T>(0.0, 0.0, 1.0));
	const auto& expected = Matrix3d<T>::Identity();
	const auto& actual = c.getRotationMatrix();
	EXPECT_EQ(expected, actual);
}

TEST(ICameraTest, TestGetRotationMatrixYZ)
{
	ConcreteCamera<T> c;
	c.move(Vector3d<T>(1.0, 0.0, 0.0));
	const auto& expected = Matrix3d<T>::Identity();
	const auto& actual = c.getRotationMatrix();
	//EXPECT_EQ(expected, actual);
}

/*
TEST(ICameraTest, TestGetModelViewMatrix)
{
	getModelviewMatrix()
}
*/

TEST(ICameraTest, TestGetUpVector)
{
	ConcreteCamera<T> c;
	EXPECT_EQ( Vector3d<T>(0,1,0), c.getUpVector() );
}

TEST(ICameraTest, TestGetForwardVector)
{
	ConcreteCamera<T> c;
	c.moveTo(Vector3d<float>(0, 0, -1));
	EXPECT_EQ(Vector3d<T>(0, 0, 1), c.getForwardVector());
}

TEST(ICameraTest, TestGetRightVector)
{
	ConcreteCamera<T> c;
	c.moveTo(Vector3d<float>(-1, 0, 0));
	EXPECT_EQ(Vector3d<T>(0, 0, 1), c.getRightVector());
}

TEST(ICameraTest, TestGetBillBoardMatrix)
{
	ConcreteCamera<T> c;
	c.setCameraXY();
	const auto actual = c.getBillboardMatrix();
}