#include "ShaderPolygon.h"
#include "../Polygon/PolygonMesh.h"
#include "../Graphics/Light.h"
#include "../Graphics/Material.h"
#include "VisualMaterial.h"
#include "ShaderCollection.h"
#include <algorithm>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

ShaderPolygon::ShaderPolygon(const VisualPolygon& vp)
{
	setup(vp);
}


void ShaderPolygon::setup(const VisualPolygon& vp)
{
	renderer.build();

	triangleBuffer.add(*vp.getPolygon());
	const auto mm = vp.getMaterialMaps();
	for (auto m : mm) {
		VisualMaterial vm(m);
		materials.push_back(vm);
	}
}

void ShaderPolygon::draw(const ICamera<float>& camera, const PointLight<float>& light)
{
	renderer.render(camera, triangleBuffer, light, materials);
}