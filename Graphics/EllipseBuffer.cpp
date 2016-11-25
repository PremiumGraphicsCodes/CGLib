#include "stdafx.h"
#include "EllipseBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void EllipseBuffer::add(const Ellipse<float>& ellipse, const ColorRGBA<float>& color)
{
	positions.add(ellipse.getCenter());
	radii.add(ellipse.getRadii());
	colors.add(color);
	angles.add(ellipse.getAngle().getRadian().get());
}
