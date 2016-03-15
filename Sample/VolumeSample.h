#ifndef __CRYSTAL_SAMPLE_VOLUME_SAMPLE_H__
#define __CRYSTAL_SAMPLE_VOLUME_SAMPLE_H__

#include "glfw.h"

#include "ISample.h"
#include "../Polygon/VolumeObject.h"
#include <memory>

class VolumeSample : public ISample
{
public:
	void setup() override;

	void demonstrate() override;

private:
	std::unique_ptr<Crystal::Polygon::VolumeObject> volume;

};

#endif