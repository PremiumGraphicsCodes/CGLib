#ifndef __CRYSTAL_MATH_SPH_KERNEL_H__
#define __CRYSTAL_MATH_SPH_KERNEL_H__

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class SPHKernel
{
public:
	SPHKernel() {};

	float getPoly6Kernel(const T distance, const T effectLength);


	Math::Vector3d<T> getPoly6KernelGradient(const Math::Vector3d<T>& distanceVector, const T effectLength);

	float getPoly6KernelLaplacian(const T distance, const T effectLength);

	Math::Vector3d<T> getSpikyKernelGradient(const Math::Vector3d<T> &distanceVector, const float effectLength);

	float getViscosityKernelLaplacian(const T distance, const T effectLength);

	T getCubicSpline(const T q);
};
	}
}

#endif