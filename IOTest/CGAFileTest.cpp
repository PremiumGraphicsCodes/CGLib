#include "gtest\gtest.h"

#include "../IO/CGAFile.h"

using namespace Crystal::IO;

TEST(CGAFileTest, TestRead)
{
	std::stringstream stream;
	stream
		<< "CGStudioActorFile" << std::endl
		<< "1" << std::endl
		<< "1" << std::endl
		<< "Actor1" << std::endl
		<< "2" << std::endl
		<< "0 0.5 0.0 0.0 0.0" << std::endl
		<< "1 0.5 1.0 0.0 0.0" << std::endl
		<< "1" << std::endl
		<< "0 0.5 0 1" << std::endl;
	CGAFile file;
	file.read(stream);
	const auto& actual = file.getActors();
	EXPECT_EQ(1, actual.size());
	for (auto& a : actual) {
		delete a;
	}
}