#ifndef __CRYSTAL_PHYSICS_SPH_KERNEL_H__
#define __CRYSTAL_PHYSICS_SPH_KERNEL_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Physics {

template<typename GeomType>
class SPHKernel
{
public:
	float getPoly6Kernel(const GeomType distance, const GeomType effectLength) {
		const auto poly6Constant = 315.0f / (64.0f * Math::Tolerance<GeomType>::getPI() * pow(effectLength, 9));
		return poly6Constant * pow(effectLength * effectLength - distance * distance, 3);
	}

	Math::Vector3d<GeomType> getPoly6KernelGradient(const Math::Vector3d<GeomType>& distanceVector, const GeomType effectLength) {
		const auto distance = distanceVector.getLength();
		const auto poly6ConstantGradient = 945.0f / (32.0f * Tolerance<GeomType>::getPI() * pow(effectLength, 9));
		const auto factor = poly6ConstantGradient * pow(effectLength * effectLength - distance * distance, 2);
		return distanceVector * factor;
	}

	float getPoly6KernelLaplacian(const GeomType distance, const GeomType effectLength) {
		const auto poly6ConstantLaplacian = 945.0f / (32.0f * Tolerance<GeomType>::getPI() * pow(effectLength, 9));
		return poly6ConstantLaplacian * (effectLength * effectLength - distance * distance)
			* (42.0f * distance * distance - 18.0f * effectLength * effectLength);
	}

	Math::Vector3d<GeomType> getSpikyKernelGradient(const Math::Vector3d<GeomType> &distanceVector, const float effectLength) {
		const auto constant = 45.0f / (Math::Tolerance<GeomType>::getPI() * pow(effectLength, 6));
		const auto distance = distanceVector.getLength();
		return distanceVector * constant * pow(effectLength - distance, 2) / distance;
	}

	float getViscosityKernelLaplacian(const GeomType distance, const GeomType effectLength) {
		const auto constant = 45.0f / (Math::Tolerance<GeomType>::getPI() * pow(effectLength, 6));
		return (effectLength - distance) * constant;
	}

};
	}
}

#endif