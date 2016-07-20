#include "stdafx.h"
#include "PointIdBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;

void PointIdBuffer::clear()
{
	position.clear();
	sizes.clear();
	idColor.clear();
}

void PointIdBuffer::add(const Vector3d<float>& position, const float size, const DrawableID did)
{
	this->position.add(position);
	this->sizes.add(size);
	this->idColor.add(did.toColor());
}