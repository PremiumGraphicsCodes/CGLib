#ifndef __CRYSTAL_SHADER_VISUAL_OBJECT_H__
#define __CRYSTAL_SHADER_VISUAL_OBJECT_H__

#include "../Polygon/PolygonObject.h"
#include "../Polygon/ParticleObject.h"

#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"

#include "../Graphics/ICamera.h"

#include "LegacyRenderer.h"

namespace Crystal {
	namespace Shader {

		enum class RenderingMode {
			Surface,
			Wireframe,
			Point,
			ID,
			Volume,
		};



class VisualObject
{
public:

	void add(const Polygon::PolygonObject& polygon)
	{
		pointBuffer.add(polygon);
		lineBuffer.add(polygon);
		triangleBuffer.add(polygon);
	}

	void add(const Polygon::ParticleObject& particle)
	{
		pointBuffer.add(particle);
	}

	void add(const Polygon::ActorObject& actor)
	{
		pointBuffer.add(actor);
		lineBuffer.add(actor);
			//triangleBuffer.add(actor);
	}

	void clear() {
		pointBuffer.clear();
		lineBuffer.clear();
		triangleBuffer.clear();
	}

	void render(const Graphics::ICamera<float>& camera, RenderingMode mode);

private:
	Graphics::PointBuffer pointBuffer;
	Graphics::LineBuffer lineBuffer;
	Graphics::TriangleBuffer triangleBuffer;

	Shader::LegacyRenderer renderer;

};

	}
}

#endif