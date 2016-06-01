#ifndef __CRYSTAL_CORE_ANISOTOROPIC_PARTICLE_H__
#define __CRYSTAL_CORE_ANISOTOROPIC_PARTICLE_H__

#include "Particle.h"

#include "../Math/Ellipsoid.h"
#include "../Math/Quaternion.h"

namespace Crystal {
	namespace Core {

class AnisotoropicParticle : public IParticle
{
public:
	AnisotoropicParticle(const int id = -1);

	explicit AnisotoropicParticle(const Math::Ellipsoid<float>& ellipsoid, const float density, const int id = -1);

	Math::Matrix3d<float> getMatrix() const;

	void rotate(const Math::Quaternion<float>& q);

	//void scale(const Math::)

private:
	Math::Vector3d<float> scale;
	Math::Quaternion<float> orientation;

	//Math::Matrix3d<float> matrix;
};
	}
}

#endif