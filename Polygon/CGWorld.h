#ifndef __CRYSTAL_POLYGON_CG_WORLD_H__
#define __CRYSTAL_POLYGON_CG_WORLD_H__

#include <vector>
#include "CGModel.h"

namespace Crystal {
	namespace Polygon {

class CGWorld
{
public:
	void add(CGModel* model) {
		this->models.push_back(model);
	}

	std::vector<PolygonMesh*> getPolygons();

	std::vector<Actor*> getActors();

private:
	std::vector<CGModel*> models;
};

	}
}

#endif