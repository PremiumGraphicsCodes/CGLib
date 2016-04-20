#ifndef __CRYSTAL_SHADER_FLUID_RENDERER_H__
#define __CRYSTAL_SHADER_FLUID_RENDERER_H__

#include "ParticleDepthRenderer.h"
#include "FrameBuffer.h"
#include "NormalFilter.h"
#include "PointRenderer.h"
#include "BilateralFilter.h"
#include "AbsorptionRenderer.h"
#include "DeferredRenderer.h"
#include "OnScreenRenderer.h"
#include "CubeMapTexture.h"
#include "SSCubeMapRenderer.h"
#include "SkyBoxRenderer.h"
#include "ThicknessRenderer.h"
#include "DepthBuffer.h"

namespace Crystal {
	namespace Shader {

class FluidRenderer
{
public:
	void build(const int width, const int height);

	void render(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera, const Crystal::Graphics::PointBuffer& buffer, const Graphics::PointLight<float>& light, const Graphics::Material& material, const CubeMapTexture& cubeMapTexture);

	void setBackgroundTexture(const Texturef& texture) { this->backgroundTexture = texture; }

	void setBackgroundDepthTexture(const DepthTexture& texture) { this->backgroundDepthTexture = texture; }

	DepthTexture* getDepthTexture() { return depthBuffer.getTexture(); }

	ITexture* getBluredTexture1() { return bluredBuffer1.getTexture(); }

	ITexture* getBluredTexture2() { return bluredBuffer2.getTexture(); }

	ITexture* getVolumeTexture() { return volumeBuffer.getTexture(); }

	ITexture* getCubeMapTexture() { return cubeMapBuffer.getTexture(); }

	ITexture* getThicknessTexture() { return volumeBuffer.getTexture(); }

	ITexture* getNormalTexture() { return normalBuffer.getTexture(); }

private:
	ParticleDepthRenderer depthRenderer;
	DepthBuffer depthBuffer;
	Texturef backgroundTexture;

	DepthTexture backgroundDepthTexture;

	NormalFilter normalFilter;
	FrameBuffer normalBuffer;

	ThicknessRenderer thicknessRenderer;
	FrameBuffer volumeBuffer;
	FrameBuffer bluredVolumeBuffer;

	FrameBuffer shadedBuffer;
	
	BilateralFilter bilateralFilter;
	FrameBuffer bluredBuffer1;
	FrameBuffer bluredBuffer2;

	AbsorptionRenderer absorptionRenderer;
	FrameBuffer absorptionBuffer;

	DeferredRenderer deferredRenderer;
	OnScreenRenderer onScreenRenderer;
	SSCubeMapRenderer cubeMapRenderer;
	FrameBufferf cubeMapBuffer;

	DepthTexture depthTexture;

	FrameBufferf fluidBuffer;

private:
	std::string getBuiltinVertexShaderSource();

	std::string getBuiltinFragmentShaderSource();

	void findLocation();

	ShaderObject shader;
};

	}
}

#endif