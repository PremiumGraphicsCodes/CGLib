#ifndef __CRYSTAL_MATH_SPH_KERNEL_H__
#define __CRYSTAL_MATH_SPH_KERNEL_H__

#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"

namespace Crystal {
	namespace Math {

template<typename T, typename int DIM = 3>
class SPHKernel
{
public:
	SPHKernel() = default;

	SPHKernel(const T effectLength);

	T getPoly6Kernel(const T distance);

	T getPoly6Kernel2(const T distanceSquared);

	T getPoly6Kernel(const T distance, const T effectLength);

	Math::Vector3d<T> getPoly6KernelGradient(const Math::Vector3d<T>& distanceVector, const T effectLength);

	T getPoly6KernelLaplacian(const T distance, const T effectLength);

	Math::Vector3d<T> getSpikyKernelGradient(const Math::Vector3d<T> &distanceVector);

	Math::Vector3d<T> getSpikyKernelGradient(const Math::Vector3d<T> &distanceVector, const T effectLength);

	T getViscosityKernelLaplacian(const T distance, const T effectLength);

	T getCubicSpline(const T q);

	T getCubicSpline(const T distance, const T effectRadius);

	Vector3d<T> getCubicSplineGradient(const Math::Vector3d<T>& distanceVector);

	Vector3d<T> getCubicSplineGradient(const Math::Vector3d<T>& distanceVector, const T effectRadius);

	T getCubicSpline(const Vector3d<T>& v, const T effectLength);

	T getCubicSpline(const Vector3d<T>& v, const Matrix3d<T>& m);

private:
	T effectLength;
	T poly6KernelConstant;
	T spikyKernelGradConstant;
	T effectLengthSquared;
};
	}
}

#endif