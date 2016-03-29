#ifndef __CRYSTAL_SAMPLE_I_SAMPLE_H__
#define __CRYSTAL_SAMPLE_I_SAMPLE_H__

#include "../Graphics/ICamera.h"

class ISample
{
public:
	ISample() {
	};

	virtual void setup() = 0;

	virtual ~ISample() {
		cleanup();
	};

	virtual void demonstrate(const Crystal::Graphics::ICamera<float>& camera) = 0;

	virtual void cleanup() {};

	virtual void onLeftDragging(const float dx, const float dy) {}

	virtual void onLeftButtonDown(const float x, const float y) {};

	virtual void onLeftButtonUp(const float x, const float y) {};

	virtual void onMouseMove(const float x, const float y) {};

private:
};

#endif