#include "gtest/gtest.h"

#include "../Graphics/Surface.h"
#include "../IO/POVFile.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

TEST(POVFileTest, TestWrite)
{
	POVFile file;
	std::string dest("../TestFile/IO/POVFileTestWrite.pov");
	Surface<float> surface;
	Triangle<float> triangle1( Vector3d<float>(0, 0, 0), Vector3d<float>(1,0,0), Vector3d<float>(1,1,0) );
	Triangle<float> triangle2(Vector3d<float>(1, 0, 0), Vector3d<float>(2, 0, 0), Vector3d<float>(2, 1, 0));
	surface.add(triangle1);
	surface.add(triangle2);
	EXPECT_TRUE(file.write(dest, surface));
}