#if _WIN64
#include "windows.h"
#endif
#include "gtest\gtest.h"

#include "../Shader/ShaderObject.h"

using namespace Crystal::Shader;

TEST(ShaderObjectTest, TestBuild)
{
	ShaderObject object;
	EXPECT_FALSE( object.build("", "") );
	assert(glGetError() == GL_NO_ERROR);

}

TEST(ShaderObjectTest, TestBuildValid)
{
	ShaderObject object;
	EXPECT_TRUE( object.build(Crystal::File("../GLSL/billboard.vs"), Crystal::File("../GLSL/billboard.gs"), Crystal::File("../GLSL/billboard.fs")) );
	assert(glGetError() == GL_NO_ERROR);
}