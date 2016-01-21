#if _WIN64
#include "windows.h"
#endif

#include "gtest/gtest.h"

#include "../Shader/Texture.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TEST(TextureTest, Test)
{
	Texture<unsigned char> texture;
	EXPECT_TRUE( texture.create(Image<unsigned char>(32, 32)) );
}