#include "gtest\gtest.h"

#include "../IO/CGAFile.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::IO;

namespace {
	std::stringstream getStr() {
		std::stringstream stream;
		stream
			<< "CGStudioActorFile" << std::endl
			<< "1" << std::endl
			<< "1" << std::endl
			<< "Actor1" << std::endl
			<< "2" << std::endl
			<< "0.5 0 0 0" << std::endl
			<< "0.5 1 0 0" << std::endl
			<< "1" << std::endl
			<< "0.5 0 1" << std::endl;
		return stream;
	}
}

TEST(CGAFileTest, TestRead)
{
	std::stringstream stream = getStr();
	CGAFile file;
	file.read(stream);
	const auto& actual = file.getActors();
	EXPECT_EQ(1, actual.size());
	for (auto& a : actual) {
		delete a;
	}
}

TEST(CGAFileTest, TestWrite)
{
	Actor actor("Actor1");
	auto j1 = actor.createJoint(Vector3d<float>(0, 0, 0), 0.5f);
	auto j2 = actor.createJoint(Vector3d<float>(1, 0, 0), 0.5f);
	actor.createBone(j1, j2, 0.5f);
	CGAFile file({ &actor });
	std::ostringstream stream;
	file.write(stream);
	EXPECT_EQ(stream.str(), getStr().str());
}