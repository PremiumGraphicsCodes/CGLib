#include "gtest/gtest.h"

#include "../Graphics/IBuffer.h"
#include "../Graphics/Buffer2d.h"
#include "../Graphics/Buffer3d.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

using T = float;

TEST(Buffer2dTest, TestGet)
{
	std::vector<T> v{ 0, 1, 1, 0 };
	Buffer2d<T> buffer(v);
	EXPECT_EQ( Vector2d<T>( 0, 1), buffer.get(0) );
}

TEST(Buffer3dTest, TestGet)
{
	std::vector<T> v{ 0, 1, 2, 10, 11, 12 };
	Buffer3d<T> buffer(v);
	EXPECT_EQ( Vector3d<T>( 0,  1,  2), buffer.get(0) );
	EXPECT_EQ( Vector3d<T>(10, 11, 12), buffer.get(1));
}