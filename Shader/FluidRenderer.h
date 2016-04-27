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
#include "SSRefractionRenderer.h"
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

	ITexture* getShadedTexture() { return shadedBuffer.getTexture(); }

	ITexture* getBluredDepthTexture() { return bluredDepthBuffer.getTexture(); }

	ITexture* getVolumeTexture() { return volumeBuffer.getTexture(); }

	ITexture* getCubeMapTexture() { return reflectionBuffer.getTexture(); }

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
	FrameBufferf bluredDepthBuffer;

	AbsorptionRenderer absorptionRenderer;
	FrameBuffer absorptionBuffer;

	DeferredRenderer deferredRenderer;
	OnScreenRenderer onScreenRenderer;
	SSReflectionRenderer reflectionRenderer;
	SSRefractionRenderer refractionRenderer;
	
	FrameBuffer reflectionBuffer;
	FrameBuffer refractionBuffer;

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