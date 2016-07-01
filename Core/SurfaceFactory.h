#ifndef __CRYSTAL_CORE_SURFACE_FACTORY_H__
#define __CRYSTAL_CORE_SURFACE_FACTORY_H__

#include "NodeCollection.h"
#include "EdgeCollection.h"
#include "FaceCollection.h"

namespace Crystal {
	namespace Core {
		class Surface;

class SurfaceFactory
{
public:
	Surface* create(const Math::Curve3d<float>& curve, const int id = -1);

	Surface* create(const Math::CircularCurve3d<float>& curve, const int id = -1);

	Surface* create(const Math::TriangleCurve3d<float>& curve, const int id = -1);

private:
	Face* createTriangleFace(Node* n1, Node* n2, Node* n3);

	Surface* create(int id);

	NodeCollection nodes;
	EdgeCollection edges;
	FaceCollection_ faces;
};

	}
}

#endif