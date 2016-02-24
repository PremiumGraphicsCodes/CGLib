#include "VMDFile.h"

#include <fstream>

using namespace Crystal::IO;

VMDHeader::VMDHeader():
	header("Vocaloid Motion Data 0002")
{

}


bool VMDHeader::read(std::istream& stream)
{
	stream.read(header, sizeof(header));
	stream.read(modelName, sizeof(modelName));
	return stream.good();
}

bool VMDHeader::write(std::ostream& stream)
{
	stream.write(header, sizeof(header));
	stream.write(modelName, sizeof(modelName));
	return stream.good();
}

bool VMDMotion::read(std::istream& stream)
{
	stream.read(boneName, sizeof(boneName));
	stream.read((char*)&frameNumber, sizeof(frameNumber));
	stream.read((char*)&location, sizeof(location));
	stream.read((char*)&rotation, sizeof(rotation));
	stream.read((char*)&interpolation, sizeof(interpolation));
	return stream.good();
}

bool VMDSkin::read(std::istream& stream)
{
	stream.read(name, sizeof(name));
	stream.read((char*)&frameNumber, sizeof(frameNumber));
	stream.read((char*)&weight, sizeof(weight));
	return stream.good();
}

bool VMDCamera::read(std::istream& stream)
{
	stream.read((char*)&flameNumber, sizeof(flameNumber));
	stream.read((char*)&length, sizeof(length));
	stream.read((char*)&location, sizeof(location));
	stream.read((char*)&rotation, sizeof(rotation));
	stream.read((char*)&interpolation, sizeof(interpolation));
	stream.read((char*)&viewAngle, sizeof(viewAngle));
	stream.read((char*)&perspective, sizeof(perspective));
	return stream.good();
}

bool VMDLight::read(std::istream& stream)
{
	stream.read((char*)&flameNumber, sizeof(flameNumber));
	stream.read((char*)&rgb, sizeof(rgb));
	stream.read((char*)&location, sizeof(location));
	return stream.good();
}

bool VMDSelfShadow::read(std::istream& stream)
{
	stream.read((char*)&frameNumber, sizeof(frameNumber));
	stream.read((char*)&mode, sizeof(mode));
	stream.read((char*)&distance, sizeof(distance));
	return stream.good();
}


bool VMDFile::read(const std::string& filename)
{
	std::ifstream stream(filename, std::ios::binary);
	if (!stream.is_open()) {
		return false;
	}
	header.read(stream);
	DWORD motionNumber = 0;
	stream.read((char*)&motionNumber, sizeof(motionNumber));
	for (unsigned int i = 0; i < motionNumber; ++i) {
		VMDMotion motion;
		motion.read(stream);
		motions.emplace_back(motion);
	}
	DWORD skinNumber = 0;
	stream.read((char*)&skinNumber, sizeof(skinNumber));
	for (unsigned int i = 0; i < skinNumber; ++i) {
		VMDSkin skin;
		skin.read(stream);
		skins.emplace_back(skin);
	}
	DWORD cameraNumber = 0;
	stream.read((char*)&cameraNumber, sizeof(cameraNumber));
	for (unsigned int i = 0; i < cameraNumber; ++i) {
		VMDCamera camera;
		camera.read(stream);
		cameras.emplace_back(camera);
	}
	DWORD lightNumber = 0;
	stream.read((char*)&lightNumber, sizeof(lightNumber));
	for (unsigned int i = 0; i < lightNumber; ++i) {
		VMDLight light;
		light.read(stream);
		lights.emplace_back(light);
	}
	DWORD selfShadowNumber = 0;
	stream.read((char*)&selfShadowNumber, sizeof(selfShadowNumber));
	for (unsigned int i = 0; i < selfShadowNumber; ++i) {
		VMDSelfShadow shadow;
		shadow.read(stream);
		selfShadows.emplace_back(shadow);
	}

	return stream.good();
}

bool VMDFile::write(const std::string& filename)
{
	return false;
}
