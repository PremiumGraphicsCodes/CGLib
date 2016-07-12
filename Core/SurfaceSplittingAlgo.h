#ifndef __CRYSTAL_CORE_SURFACE_SPLITTING_ALGO_H__
#define __CRYSTAL_CORE_SURFACE_SPLITTING_ALGO_H__

#include "PolygonMesh.h"

#include "NodeCollection.h"

namespace Crystal {
	namespace Core {

class SurfaceSplittingAlgo
{
public:

	SurfaceSplittingAlgo(PolygonMesh* s) :
		surface(s)
	{}

	void splitByNode(TriFace* f);

	void splitByCenter(TriFace* f);

	void splitByBottom(TriFace* f);

private:

	PolygonMesh* surface;

};

	}
}
#endif