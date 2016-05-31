#ifndef __CRYSTAL_SAMPLE_IO_SAMPLE_H__
#define __CRYSTAL_SAMPLE_IO_SAMPLE_H__

#include "ISample.h"
#include "../Core/PolygonMesh.h"
#include <memory>

class IOSample : public ISample
{
public:
	IOSample() {};

	~IOSample() {};

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

private:
	void setup() override;

private:
	std::unique_ptr< Crystal::Core::PolygonMesh > polygon;
};

#endif
