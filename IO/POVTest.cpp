#include "gtest/gtest.h"

#include "../Graphics/Surface.h"
#include "../IO/POVFile.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

TEST(POVFileTest, TestWrite)
{
	POVFile file;
	Crystal::File dest("../TestFile/IO/POVFileTestWrite.pov");
	Surface<float> surface;
	Triangle<float> triangle( Vector3d<float>(0, 0, 0), Vector3d<float>(1,0,0), Vector3d<float>(1,1,0) );
	surface.add(triangle);
	EXPECT_TRUE(file.write(dest, surface));
}