#ifndef __CRYSTAL_SAMPLE_IO_SAMPLE_H__
#define __CRYSTAL_SAMPLE_IO_SAMPLE_H__

#include "ISample.h"
#include "../Polygon/PolygonObject.h"
#include <memory>

class IOSample : public ISample
{
public:
	IOSample() {};

	~IOSample() {};

	void demonstrate() override;

private:
	void setup() override;

private:
	std::unique_ptr< Crystal::Polygon::PolygonObject > polygon;
};

#endif
