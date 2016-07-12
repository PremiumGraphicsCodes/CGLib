#ifndef __CRYSTAL_CORE_SURFACE_SPLITTING_ALGO_H__
#define __CRYSTAL_CORE_SURFACE_SPLITTING_ALGO_H__

#include "PolygonMesh.h"


namespace Crystal {
	namespace Core {

class SurfaceSplittingAlgo
{
public:

	SurfaceSplittingAlgo(PolygonMesh* s) :
		surface(s)
	{}


	void splitByCenter(Face* f);

	void splitByBottom(Face* f);

private:

	PolygonMesh* surface;

};

	}
}
#endif