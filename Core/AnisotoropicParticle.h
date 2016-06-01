#ifndef __CRYSTAL_CORE_ANISOTOROPIC_PARTICLE_H__
#define __CRYSTAL_CORE_ANISOTOROPIC_PARTICLE_H__

#include "Particle.h"

#include "../Math/Ellipsoid.h"
#include "../Math/Quaternion.h"

namespace Crystal {
	namespace Core {

class AnisotoropicParticle : public Particle
{
public:
	AnisotoropicParticle(const int id = -1);

	explicit AnisotoropicParticle(const Math::Ellipsoid<float>& ellipsoid, const int id = -1);

	Math::Matrix3d<float> getMatrix() const;

private:
	Math::Vector3d<float> scale;
	Math::Quaternion<float> orientation;

	//Math::Matrix3d<float> matrix;
};
	}
}

#endif