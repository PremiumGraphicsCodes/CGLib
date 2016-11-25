#ifndef __CRYSTAL_GRAPHICS_ELLIPSE_BUFFER_H__
#define __CRYSTAL_GRAPHICS_ELLIPSE_BUFFER_H__

#include "Buffer1d.h"
#include "Buffer2d.h"
#include "Buffer3d.h"
#include "Buffer4d.h"

#include "../Math/Ellipse.h"

namespace Crystal {
	namespace Graphics {

class EllipseBuffer
{
public:
	void add(const Math::Ellipse<float>& ellipse, const ColorRGBA<float>& color);

	Buffer3d<float> getPositions() const { return positions; }

	Buffer2d<float> getRadii() const { return radii; }

	Buffer4d<float> getColors() const { return colors; }

	Buffer1d<float> getAngles() const { return angles; }

private:
	Buffer3d<float> positions;
	Buffer2d<float> radii;
	Buffer4d<float> colors;
	Buffer1d<float> angles;
};

	}
}

#endif