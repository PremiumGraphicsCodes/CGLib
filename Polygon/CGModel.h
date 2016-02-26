#ifndef __CRYSTAL_POLYGON_CG_MODEL_H__
#define __CRYSTAL_POLYGON_CG_MODEL_H__

#include "PolygonObject.h"
#include "ActorObject.h"
#include "ParticleObject.h"

#include <memory>

namespace Crystal {
	namespace Polygon {

class CGModel
{
public:
	CGModel(PolygonObject* polygon) :
		polygon(polygon)
	{}

	CGModel(PolygonObject* polygon, ActorObject* actor) :
		polygon(polygon),
		actor(actor)
	{}

	CGModel(PolygonObject* polygon, ActorObject* actor, ParticleObject* particle) :
		polygon(polygon),
		actor(actor),
		particle(particle)
	{}

private:
	std::unique_ptr< Polygon::PolygonObject > polygon;
	std::unique_ptr< Polygon::ActorObject > actor;
	std::unique_ptr< Polygon::ParticleObject > particle;
};

	}
}

#endif