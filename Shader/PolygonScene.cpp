#include "PolygonScene.h"
#include "../Core/PolygonMesh.h"
#include "../Graphics/Light.h"
#include "../Graphics/Material.h"
#include "VisualMaterial.h"
#include <algorithm>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

PolygonScene::PolygonScene(const VisualPolygon& vp)
{
	setup(vp);
}


void PolygonScene::setup(const VisualPolygon& vp)
{
	renderer.build();

	triangleBuffer.add(*vp.getPolygon());
	const auto mm = vp.getMaterialMaps();
	for (auto m : mm) {
		VisualMaterial vm(m);
		materials.push_back(vm);
	}
}

void PolygonScene::draw(const ICamera<float>& camera, const PointLight<float>& light)
{
	renderer.render(camera, triangleBuffer, light, materials);
}