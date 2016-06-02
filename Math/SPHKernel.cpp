#include "SPHKernel.h"

using namespace Crystal::Math;

template<typename T>
float SPHKernel<T>::getPoly6Kernel(const T distance, const T effectLength) {
	const auto poly6Constant = 315.0f / (64.0f * Math::Tolerance<T>::getPI() * pow(effectLength, 9));
	return poly6Constant * pow(effectLength * effectLength - distance * distance, 3);
}

template<typename T>
T SPHKernel<T>::getCubicSpline(const T q)
{
	const auto coe = T{ 3 } / Tolerance<T>::getTwoPI();
	if (q < 1) {
		return coe * (T{2}/T{3}-q*q + T{0.5}*q*q*q);
	}
	else if (q < 2) {
		return coe * (std::pow(2 - q, 3) / T{ 6 });
	}
	else {
		return 0;
	}
}


template<typename T>
Vector3d<T> SPHKernel<T>::getPoly6KernelGradient(const Vector3d<T>& distanceVector, const T effectLength) {
	const auto distance = distanceVector.getLength();
	const auto poly6ConstantGradient = 945.0f / (32.0f * Tolerance<T>::getPI() * pow(effectLength, 9));
	const auto factor = poly6ConstantGradient * pow(effectLength * effectLength - distance * distance, 2);
	return distanceVector * factor;
}

template<typename T>
float SPHKernel<T>::getPoly6KernelLaplacian(const T distance, const T effectLength)
{
	const auto poly6ConstantLaplacian = 945.0f / (32.0f * Tolerance<T>::getPI() * pow(effectLength, 9));
	return poly6ConstantLaplacian * (effectLength * effectLength - distance * distance)
		* (42.0f * distance * distance - 18.0f * effectLength * effectLength);
}

template<typename T>
Vector3d<T> SPHKernel<T>::getSpikyKernelGradient(const Vector3d<T> &distanceVector, const float effectLength)
{
	const auto constant = 45.0f / (Math::Tolerance<T>::getPI() * pow(effectLength, 6));
	const auto distance = distanceVector.getLength();
	return distanceVector * constant * pow(effectLength - distance, 2) / distance;
}

template<typename T>
float SPHKernel<T>::getViscosityKernelLaplacian(const T distance, const T effectLength)
{
	const auto constant = 45.0f / (Math::Tolerance<T>::getPI() * pow(effectLength, 6));
	return (effectLength - distance) * constant;
}


template class SPHKernel<float>;
