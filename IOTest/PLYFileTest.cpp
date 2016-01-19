#include "gtest/gtest.h"

#include "PLYFile.h"

using namespace Crystal::IO;

TEST(PLYFileTest, TestRead)
{
	std::stringstream stream;
	stream
		<< "ply" << std::endl
		<< "format ascii 1.0" << std::endl
		<< "comment Kinect v1 generated" << std::endl
		<< "element vertex 3" << std::endl
		<< "property double x" << std::endl
		<< "property double y" << std::endl
		<< "property double z" << std::endl
		<< "end_header" << std::endl
		<< "0.0 0.0 0.0" << std::endl
		<< "1.0 2.0 3.0" << std::endl
		<< "3.0 2.0 1.0" << std::endl;
}