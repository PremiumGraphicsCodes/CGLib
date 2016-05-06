#ifndef __CRYSTAL_IO_PMM_FILE_H__
#define __CRYSTAL_IO_PMM_FILE_H__

#include <istream>
#include <ostream>
#include <vector>
#include "../Math/Vector3d.h"
#include "../Math/Quaternion.h"

namespace Crystal {
	namespace IO {

using DWORD = unsigned long;
using BYTE = unsigned char;
using WORD = unsigned short;

class PMMHeader
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

private:
	char formatId[30];
	int viewWidth;
	int viewHeight;
	int frameWidth;
	float viewAngle;
	BYTE flag[7];
};

class PMMModelColletion
{
private:
	int number;

};

class PMMModelHeader
{
public:
	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;
private:
	unsigned char modelNumber;
	char nameInJapanese[256];
	char nameInEnglish[256];
	char modelPath[256];
	char unknown;
	int boneCount;
	std::vector<std::string> boneNames;
	int skinCount;
	std::vector<std::string> skinNames;
	int ikCount;
	std::vector<int> iks;

	char frameCount;
	std::vector<bool> isFrameOpen;
	int startFrame;
	int lastFrame;
};

class PMMInitialBoneKeyFrame
{
private:
	int frameNumber;
	int previousIndex;
	int nextIndex;
	float interpolationCurveX[4];
	float interpolationCurveY[4];
	float interpolationCurveZ[4];
	float interpolationCurveR[4];
	char unknown;
	bool isSelected;
};

class PMMBoneKeyFrame
{
public:
private:
	int currentIndex;
	int frameNumber;
	int previousIndex;
	int nextIndex;
	float interpolationCurveX[4];
	float interpolationCurveY[4];
	float interpolationCurveZ[4];
	float interpolationCurveR[4];
	Math::Vector3d<float> translation;
	Math::Quaternion<float> orientation;
	bool padding;
	bool isSelected;
};

class PMMBoneKeyFrameCollection
{
public:
private:
	std::vector<PMMBoneKeyFrame> keyFrames;
};

class PMMCameraKeyFrame
{
private:
	int currentIndex;
	int frame;
	int previousIndex;
	int nextIndex;
	float distance;
	Math::Vector3d<float> position;
	Math::Vector3d<float> angle;
	int followingModelIndex;
	int followingBoneIndex;
	float interpolationCurveX[4];
	float interpolationCurveY[4];
	float interpolationCurveZ[4];
	float interpolationCurveR[4];
	bool isOrtho;
	float parspectiveAngle;
	bool isSelected;
};

class PMMCameraKeyFrameCollection
{
private:
	std::vector<PMMCameraKeyFrame> keyFrames;
};

class PMMFile
{
public:

private:
	PMMHeader header;
};
	}
}

#endif