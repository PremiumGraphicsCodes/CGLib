#ifndef __CRYSTAL_CORE_I_PARTICLE_H__
#define __CRYSTAL_CORE_I_PARTICLE_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Core {

class IParticle
{
public:
	IParticle(const int id = -1) :
		id(id)
	{}

	IParticle(const Math::Vector3d<float>& position, const float density, const int id = -1) :
		position(position),
		density(density),
		id(id)
	{}

	virtual ~IParticle() = default;

protected:
	Math::Vector3d<float> position;
	float density;
	const int id;
};
	}
}

#endif