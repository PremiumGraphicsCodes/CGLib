#ifndef __CRYSTAL_CORE_SURFACE_FACTORY_H__
#define __CRYSTAL_CORE_SURFACE_FACTORY_H__

#include "../Util/UnCopyable.h"
#include "NodeCollection.h"
#include "EdgeCollection.h"
#include "FaceCollection.h"

namespace Crystal {
	namespace Core {
		class Surface;

class SurfaceFactory : private UnCopyable
{
public:
	~SurfaceFactory();

	void clear();

	Surface* create(const Math::Curve3d<float>& curve, const int id = -1);

	Surface* create(const Math::CircularCurve3d<float>& curve, const int id = -1);

	Surface* create(const Math::TriangleCurve3d<float>& curve, const int id = -1);

	void split(Face* f);

	//void remove(Node* n);

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