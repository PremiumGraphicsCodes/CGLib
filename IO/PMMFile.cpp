#include "PMMFile.h"

using namespace Crystal::IO;

bool PMMHeader::read(std::istream& stream)
{
	stream.read(formatId, sizeof(formatId));
	stream.read((char*)&viewWidth, sizeof(viewWidth));
	stream.read((char*)&viewHeight, sizeof(viewHeight));
	stream.read((char*)&frameWidth, sizeof(frameWidth));
	stream.read((char*)&viewAngle, sizeof(viewAngle));
	stream.read((char*)&flag, sizeof(flag));

	return stream.good();
}

bool PMMHeader::write(std::ostream& stream) const
{
	stream.write(formatId, sizeof(formatId));
	stream.write((char*)&viewWidth, sizeof(viewWidth));
	stream.write((char*)&frameWidth, sizeof(frameWidth));
	stream.write((char*)&viewAngle, sizeof(viewAngle));
	stream.write((char*)&flag, sizeof(flag));

	return stream.good();
}

bool PMMModelHeader::read(std::istream& stream)
{
	stream.read((char*)&modelNumber, sizeof(modelNumber));
	stream.read(nameInJapanese, sizeof(nameInJapanese));
	stream.read(nameInEnglish, sizeof(nameInEnglish));
	stream.read(modelPath, sizeof(modelPath));
	stream.read((char*)&unknown, sizeof(unknown));
	stream.read((char*)&boneCount, sizeof(boneCount));
	for (int i = 0; i < boneCount; ++i) {
		char boneName[256];
		stream.read(boneName, sizeof(boneName));
		boneNames.push_back(boneName);
	}
	for (int i = 0; i < skinCount; ++i) {
		char skinName[256];
		stream.read(skinName, sizeof(skinName));
		skinNames.push_back(skinName);
	}
	stream.read((char*)&ikCount, sizeof(ikCount));
	for (int i = 0; i < ikCount; ++i) {
		int ik;
		stream.read((char*)&ik, sizeof(ik));
		iks.push_back(ik);
	}

	/*
	char frameCount;
	std::vector<bool> isFrameOpen;
	int startFrame;
	int lastFrame;
	*/
	return false;
};
