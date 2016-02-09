#ifndef __CRYSTAL_PHYSICS_BOUNDARY_COORDINATOR_H__
#define __CRYSTAL_PHYSICS_BOUNDARY_COORDINATOR_H__

#include "Coordinator.h"

#include "../Math/Box.h"
#include "../Math/Vector3d.h"

#include <vector>

namespace Crystal{
	namespace Physics{

template<typename GeomType, typename TimeType>
class BoundaryCoordinator : public Coordinator
{
public:
	BoundaryCoordinator(const Math::Box<GeomType>& box, const TimeType timeStep ) :
		box( box ),
		timeStep( timeStep )
	{}

	~BoundaryCoordinator(void){};

	virtual void coordinate(const std::vector<Particle*>& particles) {
		#pragma omp parallel for
		for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
			particles[i]->addForce(getForce(particles[i]->getCenter() ) * particles[i]->getDensity());
		}
	}

private:
	const Math::Box<GeomType> box;
	const TimeType timeStep;

	Math::Vector3d<GeomType> getForce(const Math::Vector3d<GeomType>& center) {
		Math::Vector3d<GeomType> force = Math::Vector3d<GeomType>::Zero();

		force += getForceX(center.getX() );
		force += getForceY(center.getY() );
		force += getForceZ(center.getZ() );

		return force;

	}

	Math::Vector3d<GeomType> getForceX(const GeomType x)
	{
		GeomType over = 0;
		if (x > box.getMaxX()) {
			over = x - box.getMaxX();
		}
		else if (x < box.getMinX()) {
			over = x - box.getMinX();
		}

		const auto force = getForce(over);
		return Math::Vector3d<GeomType>::UnitX() * force;
	}

	Math::Vector3d<GeomType> getForceY(const GeomType y)
	{
		GeomType over = 0;
		if (y > box.getMaxY()) {
			over = y - box.getMaxY();
		}
		else if (y < box.getMinY()) {
			over = y - box.getMinY();
		}
		const auto force = getForce(over);
		return Math::Vector3d<GeomType>::UnitY() * force;
	}

	Math::Vector3d<GeomType> getForceZ(const GeomType z)
	{
		GeomType over = 0;
		if (z > box.getMaxZ()) {
			over = z - box.getMaxZ();
		}
		else if (z < box.getMinZ()) {
			over = z - box.getMinZ();
		}
		const GeomType force = getForce(over);
		return Math::Vector3d<GeomType>::UnitZ() * force;
	}

	GeomType getForce(const GeomType over) {
		return -over / timeStep / timeStep;
	}


};

	}
}


#endif