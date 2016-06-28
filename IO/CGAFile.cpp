#include "stdafx.h"
#include "CGAFile.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::IO;

namespace {
	const int fileFormatVersion = 2;
}

bool CGAFile::read(const File& file)
{
	std::ifstream stream(file.getFullPath());
	if (!stream.is_open()) {
		return false;
	}
	return read(stream);
}

bool CGAFile::read(std::istream& stream)
{
	std::string title;
	stream >> title;
	if (title != "CGStudioActorFile") {
		return false;
	}
	int fileFormatVersion = 0;
	stream >> fileFormatVersion;
	if (fileFormatVersion != 2) {
		return false;
	}
	int actorCount = 0;
	stream >> actorCount;
	for (int i = 0; i < actorCount; ++i) {
		Actor* actor = new Actor();
		std::string name;
		stream >> name;
		int jointCount = 0;
		stream >> jointCount;
		std::vector<Joint*> joints;
		for (int j = 0; j < jointCount; ++j) {
			float posx = 0;
			stream >> posx;
			float posy = 0;
			stream >> posy;
			float posz = 0;
			stream >> posz;
			float radiix = 0;
			stream >> radiix;
			float radiiy = 0;
			stream >> radiiy;
			float radiiz = 0;
			stream >> radiiz;
			float qx = 0;
			stream >> qx;
			float qy = 0;
			stream >> qy;
			float qz = 0;
			stream >> qz;
			float qw = 0;
			stream >> qw;
			auto joint = actor->createJoint(Vector3d<float>(posx, posy, posz), Vector3d<float>(radiix,radiiy,radiiz));
			joint->setOrientation(Quaternion<float>(qx, qy, qz, qw));
			joints.push_back(joint);
		}
		int boneCount = 0;
		stream >> boneCount;
		for (int j = 0; j < boneCount; ++j) {
			int originalJointId = 0;
			stream >> originalJointId;
			int destJointId = 0;
			stream >> destJointId;
			float radiix = 0;
			stream >> radiix;
			float radiiy = 0;
			stream >> radiiy;
			float angle = 0;
			stream >> angle;
			auto b = actor->createBone(joints[originalJointId], joints[destJointId], Vector2d<float>(radiix, radiiy));
			b->setRotation(Angle<float>(Degree<float>(angle)));
		}
		actors.push_back(actor);
	}
	//stream << actor.getBones().size() << std::endl;
	return stream.good();
}

bool CGAFile::write(const File& file)
{
	std::ofstream stream(file.getFullPath());
	if (!stream.is_open()) {
		return false;
	}
	return write(stream);
}

bool CGAFile::write(std::ostream& stream)
{
	stream << "CGStudioActorFile" << std::endl;
	stream << fileFormatVersion << std::endl;

	stream << actors.size() << std::endl;
	for (auto& actor : actors) {
		assert(!actor->getName().empty());
		stream << actor->getName() << std::endl;
		const auto& joints = actor->getJoints();
		stream << joints.size() << std::endl;
		for (auto j : joints) {
			const auto& pos = j->getPosition();
			const auto& radii = j->getRadii();
			stream
				<< pos.getX() << " "
				<< pos.getY() << " "
				<< pos.getZ() << " "
				<< radii.getX() << " "
				<< radii.getY() << " "
				<< radii.getZ() << " "
				<< j->getOrientation().getX() << " "
				<< j->getOrientation().getY() << " "
				<< j->getOrientation().getZ() << " "
				<< j->getOrientation().getW() << std::endl;
		}
		const auto& bones = actor->getBones();
		stream << bones.size() << std::endl;
		for (auto b : bones) {
			stream
				<< b->getOriginJoint()->getId() << " "
				<< b->getDestJoint()->getId() << " "
				<< b->getThickness().getX() << " "
				<< b->getThickness().getY() << " "
				<< b->getRotation().getDegree().get() << std::endl;
		}
	}
	return stream.good();

}
