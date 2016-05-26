#ifndef __CRYSTAL_SAMPLE_VOLUME_SAMPLE_H__
#define __CRYSTAL_SAMPLE_VOLUME_SAMPLE_H__

#include "glfw.h"

#include "ISample.h"
#include "../Polygon/Volume.h"
#include "../Polygon/PolygonMesh.h"
#include <memory>

class VolumeSample : public ISample
{
public:
	void setup() override;

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

private:
	std::unique_ptr<Crystal::Core::Volume> volume;
	std::unique_ptr<Crystal::Core::PolygonMesh> polygon;
};

#endif