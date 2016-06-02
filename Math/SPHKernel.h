#ifndef __CRYSTAL_MATH_SPH_KERNEL_H__
#define __CRYSTAL_MATH_SPH_KERNEL_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename GeomType>
class SPHKernel
{
public:
	SPHKernel() {};

	float getPoly6Kernel(const GeomType distance, const GeomType effectLength);

	Math::Vector3d<GeomType> getPoly6KernelGradient(const Math::Vector3d<GeomType>& distanceVector, const GeomType effectLength);

	float getPoly6KernelLaplacian(const GeomType distance, const GeomType effectLength);

	Math::Vector3d<GeomType> getSpikyKernelGradient(const Math::Vector3d<GeomType> &distanceVector, const float effectLength);

	float getViscosityKernelLaplacian(const GeomType distance, const GeomType effectLength);
};
	}
}

#endif