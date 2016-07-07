#ifndef __CRYSTAL_CORE_ANISOTOROPIC_PARTICLE_H__
#define __CRYSTAL_CORE_ANISOTOROPIC_PARTICLE_H__

#include "Particle.h"

namespace Crystal {
	namespace Core {

class AnisotoropicParticle : public IParticle
{
public:
	AnisotoropicParticle(const int id = -1);

	AnisotoropicParticle(const Math::Ellipsoid<float>& ellipsoid, const float density, const int id = -1);

	AnisotoropicParticle(const Math::Ellipsoid<float>& ellipsoid, const float density, const Math::Quaternion<float>& orientation, const int id = -1);

	Math::Matrix3d<float> getMatrix() const override;

	void rotate(const Math::Quaternion<float>& q);

	Math::Box3d<float> getBoundingBox() const override;

	float getBoundingRadius() const override;

	Math::Matrix3d<float> getScalingMatrix() const;

	Math::Matrix3d<float> getRotationMatrix() const;

	void scale(const Math::Vector3d<float>& s);

	AnisotoropicParticle* clone(const int newId = -1) const;

	Math::Vector3d<float> getRadii() const override { return radii; }

	Math::Quaternion<float> getOrientation() const override { return orientation; }

	Math::Ellipsoid<float> toEllipsoid() const override;


private:
	Math::Vector3d<float> radii;
	Math::Quaternion<float> orientation;

	//Math::Matrix3d<float> matrix;
};
	}
}

#endif