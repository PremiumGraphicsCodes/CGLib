#include "stdafx.h"
#include "SmoothingAlgo.h"
#include "Face.h"
#include "Surface.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

void SmoothingAlgo::execute(Node* center)
{
	const auto& nodes = surface->getNodes();
	Vector3d<float> position = center->getPosition();
	for (auto& n : nodes) {
		position += (n->getPosition() - center->getPosition()) / nodes.size();
	}
	center->moveTo(position);
}
