#ifndef __CRYSTAL_SAMPLE_CURSOR_3D_SAMPLE_H__
#define __CRYSTAL_SAMPLE_CURSOR_3D_SAMPLE_H__

#include "glfw.h"

#include "../Physics/Fluid.h"
#include "../Physics/PhysicsWorld.h"
#include "../Graphics/ColorMap.h"
#include "../Shader/PointRenderer.h"
#include "../Shader/IDRenderer.h"
#include "../Shader/FrameBuffer.h"
#include "ISample.h"
#include <memory>

class Cursor3dSample : public ISample
{
public:
	void setup() override;

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

	// void onKeyDown(const unsigned char c) override;

	//void onMiddleButtonDown(const float x, const float y) override;

	//void onMiddleButtonUp(const float x, const float y) override {};

	void onMiddleDragging(const float dx, const float dy) override;

private:
	Crystal::Math::Vector3d<float> cursor;
	Crystal::Shader::PointRenderer renderer;
	Crystal::Math::Matrix3d<float> rotationMatrix;
};

#endif