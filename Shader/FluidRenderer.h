#ifndef __CRYSTAL_SHADER_FLUID_RENDERER_H__
#define __CRYSTAL_SHADER_FLUID_RENDERER_H__

#include "ParticleDepthRenderer.h"
#include "FrameBuffer.h"
#include "NormalFilter.h"
#include "PointRenderer.h"
#include "BilateralFilter.h"
#include "SSAbsorptionRenderer.h"
#include "DeferredRenderer.h"
#include "OnScreenRenderer.h"
#include "CubeMapTexture.h"
#include "SSReflectionRenderer.h"
#include "SSRefractionRenderer.h"
#include "SkyBoxRenderer.h"
#include "SSThicknessRenderer.h"
#include "DepthBuffer.h"

namespace Crystal {
	namespace Shader {

class FluidRenderer
{
public:
	void build(const int width, const int height);

	void render(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera, const Crystal::Graphics::PointBuffer& buffer, const Graphics::PointLight<float>& light, const Graphics::Material& material, const CubeMapTexture& cubeMapTexture);

	void setSceneTexture(const Texture& texture) { this->sceneTexture = texture; }

	ITexture* getDepthTexture() { return &depthTexture; }

	ITexture* getShadedTexture() { return &shadedTexture; }

	ITexture* getBluredDepthTexture() { return &bluredDepthTexture; }


	ITexture* getThicknessTexture() { return &thicknessTexture; }

	ITexture* getBluredThicknessTexture() { return &bluredThicknessTexture; }

	ITexture* getVolumeTexture() { return &volumeTexture; }

	ITexture* getNormalTexture() { return &normalTexture; }

	ITexture* getFluidTexture() { return &fluidTexture; }

	ITexture* getReflectionTexture() { return &reflectionTexture; }

	ITexture* getSceneTexture() { return &sceneTexture; }


private:
	ParticleDepthRenderer depthRenderer;
	DepthBuffer depthBuffer;

	FrameBuffer frameBuffer;
	NormalFilter normalFilter;

	SSThicknessRenderer thicknessRenderer;
	
	BilateralFilter bilateralFilter;

	SSAbsorptionRenderer absorptionRenderer;

	DeferredRenderer deferredRenderer;
	SSReflectionRenderer reflectionRenderer;
	SSRefractionRenderer refractionRenderer;
	
	DepthTexture depthTexture;
	Texture sceneTexture;
	Texture shadedTexture;
	Texturef bluredDepthTexture;
	Texture normalTexture;
	Texture thicknessTexture;
	Texture bluredThicknessTexture;

	Texture volumeTexture;
	Texture reflectionTexture;
	Texture fluidTexture;

private:
	std::string getBuiltinVertexShaderSource();

	std::string getBuiltinFragmentShaderSource();

	void findLocation();

	ShaderObject shader;
};

	}
}

#endif