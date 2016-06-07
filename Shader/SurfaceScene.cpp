#include "SurfaceScene.h"
#include "../Core/PolygonMesh.h"
#include "../Graphics/Light.h"
#include "../Graphics/Material.h"
#include "VisualMaterial.h"
#include <algorithm>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

/*
SurfaceScene::SurfaceScene(const VisualSurface& vs)
{
	setup(vs);
}


void SurfaceScene::setup(const VisualSurface& vs)
{
	renderer.build();

	triangleBuffer.add(*vs.getSurface());
	const auto mm = vs.getMaterial();
	for (auto m : mm) {
		VisualMaterial vm(m);
		materials.push_back(vm);
	}
}

void SurfaceScene::draw(const ICamera<float>& camera, const PointLight<float>& light)
{
	renderer.render(camera, triangleBuffer, light, materials);
}
*/