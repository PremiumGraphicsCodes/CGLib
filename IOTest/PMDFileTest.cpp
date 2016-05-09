#include "gtest/gtest.h"
#include "../Polygon/Vertex.h"
#include "../Polygon/PolygonObject.h"
#include "../Polygon/ActorObject.h"
#include "../Polygon/Bone.h"
#include "../Graphics/VisualPolygon.h"
#include "../IO/PMDFile.h"
#include <fstream>
#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Graphics;
using namespace Crystal::IO;


TEST(PMDFileTest, TestFromPolygonObject)
{
	PolygonObject object;
	Triangle<float> triangle(Vector3d<float>(0.0, 0.0, 0.0), Vector3d<float>(1.0, 0.0, 0.0), Vector3d<float>(1.0, 1.0, 0.0));
	object.add(triangle);
	VisualPolygon vp(&object);
	PMDFile file(vp);
}

TEST(PMDFileTest, TestToActorObject)
{
	PMDBone root;
	//root.name = "root";
	root.parentBoneIndex = 0xffff;
	root.tailBoneIndex = 1;
	root.type = 0;
	root.ikParentBoneIndex = 0;
	root.boneHeadPos = Vector3d<float>(1, 2, 3);

	PMDBone child;
	//child.name = "child";
	child.parentBoneIndex = 0;
	child.tailBoneIndex = 0;
	child.type = 0;
	child.ikParentBoneIndex = 0;
	child.boneHeadPos = Vector3d<float>(3, 2, 1);

	PMDBoneCollection bones({ root, child });
	std::unique_ptr<ActorObject> actor( bones.toActorObject() );
	EXPECT_EQ( 2, actor->getJoints().size());
	EXPECT_EQ( 2, actor->getBones().size() );
	Bone* bone = actor->getBones().front();
	EXPECT_EQ(nullptr, bone->getOriginJoint());
	//EXPECT_EQ(actor->getJoints()[1], bone->getDestJoint());
	EXPECT_NE(nullptr, bone->getDestJoint());

	//PMDFile file;
	//file.add()
}

/*
TEST(PMDFileTest, TestToPolygonObject)
{
	PMDHeader header;
	//PMDVertices vertices;
	//PMDFaces faces;
	PMDFile file(); header, vertices, faces);
	auto polygon = file.toPolygonObject();
	delete polygon;
}
*/