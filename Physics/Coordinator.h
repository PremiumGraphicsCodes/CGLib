#ifndef __CRYSTAL_PHYSICS_COORDINATOR_H__
#define __CRYSTAL_PHYSICS_COORDINATOR_H__

#include <vector>

#include "Particle.h"

#include "../Math/Vector3d.h"

#include "../Util/UnCopyable.h"

#include <memory>

namespace Crystal{
	namespace Physics{

class Coordinator : private UnCopyable
{
public:
	Coordinator()
	{};

	virtual ~Coordinator(){}

	virtual void coordinate( const std::vector<Particle*>& particles ) = 0;
};

using CoordinatorSPtr = std::shared_ptr < Coordinator > ;
using CoordinatorSPtrVector = std::vector<CoordinatorSPtr>;

	}
}

#endif