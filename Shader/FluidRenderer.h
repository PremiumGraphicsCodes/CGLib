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
#include "CubeMapTextureObject.h"
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

	void render(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera, const Crystal::Graphics::PointBuffer& buffer, const Graphics::PointLight<float>& light, const Graphics::Material& material, const CubeMapTextureObject& cubeMapTexture, const Graphics::EllipsoidBuffer& ellipsoidBuffer);

	void setSceneTexture(const TextureObject& texture) { this->sceneTexture = texture; }

	ITextureObject* getDepthTexture() { return &depthTexture; }

	ITextureObject* getShadedTexture() { return &shadedTexture; }

	ITextureObject* getBluredDepthTexture() { return &bluredDepthTexture; }


	ITextureObject* getThicknessTexture() { return &thicknessTexture; }

	ITextureObject* getBluredThicknessTexture() { return &bluredThicknessTexture; }

	ITextureObject* getVolumeTexture() { return &volumeTexture; }

	ITextureObject* getNormalTexture() { return &normalTexture; }

	ITextureObject* getFluidTexture() { return &fluidTexture; }

	ITextureObject* getReflectionTexture() { return &reflectionTexture; }

	ITextureObject* getSceneTexture() { return &sceneTexture; }


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
	
	DepthTextureObject depthTexture;
	TextureObject sceneTexture;
	TextureObject shadedTexture;
	TextureObject bluredDepthTexture;
	TextureObject normalTexture;
	TextureObject thicknessTexture;
	TextureObject bluredThicknessTexture;

	TextureObject volumeTexture;
	TextureObject reflectionTexture;
	TextureObject fluidTexture;

private:
	std::string getBuiltinVertexShaderSource();

	std::string getBuiltinFragmentShaderSource();

	void findLocation();

	ShaderObject shader;
};

	}
}

#endif