#include "CGAFile.h"

#include <fstream>

using namespace Crystal::Polygon;
using namespace Crystal::IO;

namespace {
	const int fileFormatVersion = 1;
}

bool CGAFile::read(const File& file)
{
	std::ifstream stream(file.getFullPath());
	if (!stream.is_open()) {
		return false;
	}
	int bonesCount = 0;
	stream >> bonesCount;
	//stream << actor.getBones().size() << std::endl;
	return false;
}

bool CGAFile::write(const File& file)
{
	std::ofstream stream(file.getFullPath());
	if (!stream.is_open()) {
		return false;
	}
	stream << "CGStudio Actor File" << std::endl;
	stream << fileFormatVersion << std::endl;
	for (auto j : actor.getJoints()) {
		stream << j->getId() << " "
			<< j->getRadius() << " "
			<< j->getPosition().getX() << " "
			<< j->getPosition().getY() << " "
			<< j->getPosition().getZ() << std::endl;
	}

	stream << actor.getBones().size() << std::endl;
	for (auto b : actor.getBones()) {
		stream << b->getId() << " "
			<< b->getThickness() << " "
			<< b->getOriginJoint()->getId() << " "
			<< b->getDestJoint()->getId() << std::endl;
	}
	return stream.good();
}
