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
#include "SSReflectionRenderer.h"
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

	void setSceneTexture(const Texture& texture) { this->sceneTexture = texture; }

	void setSceneDepthTexture(const DepthTexture& texture) { this->sceneDepthTexture = texture; }

	DepthTexture* getDepthTexture() { return depthBuffer.getTexture(); }

	ITexture* getBluredTexture1() { return bluredBuffer1.getTexture(); }

	ITexture* getBluredTexture2() { return bluredBuffer2.getTexture(); }

	ITexture* getVolumeTexture() { return volumeBuffer.getTexture(); }

	ITexture* getCubeMapTexture() { return cubeMapBuffer.getTexture(); }

	ITexture* getThicknessTexture() { return volumeBuffer.getTexture(); }

	ITexture* getNormalTexture() { return normalBuffer.getTexture(); }

	ITexture* getFluidTexture() { return fluidBuffer.getTexture(); }

private:
	ParticleDepthRenderer depthRenderer;
	DepthBuffer depthBuffer;

	Texture sceneTexture;
	DepthTexture sceneDepthTexture;

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
	SSReflectionRenderer cubeMapRenderer;
	FrameBuffer cubeMapBuffer;

	DepthTexture depthTexture;

	FrameBuffer fluidBuffer;

private:
	std::string getBuiltinVertexShaderSource();

	std::string getBuiltinFragmentShaderSource();

	void findLocation();

	ShaderObject shader;
};

	}
}

#endif