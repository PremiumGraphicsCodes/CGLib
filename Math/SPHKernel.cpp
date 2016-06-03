#include "SPHKernel.h"

using namespace Crystal::Math;

template<typename T, typename int DIM>
float SPHKernel<T,DIM>::getPoly6Kernel(const T distance, const T effectLength) {
	const auto poly6Constant = 315.0f / (64.0f * Math::Tolerance<T>::getPI() * pow(effectLength, 9));
	return poly6Constant * pow(effectLength * effectLength - distance * distance, 3);
}

template<typename T, typename int DIM>
Vector3d<T> SPHKernel<T,DIM>::getPoly6KernelGradient(const Vector3d<T>& distanceVector, const T effectLength) {
	const auto distance = distanceVector.getLength();
	const auto poly6ConstantGradient = 945.0f / (32.0f * Tolerance<T>::getPI() * pow(effectLength, 9));
	const auto factor = poly6ConstantGradient * pow(effectLength * effectLength - distance * distance, 2);
	return distanceVector * factor;
}

template<typename T, typename int DIM>
float SPHKernel<T,DIM>::getPoly6KernelLaplacian(const T distance, const T effectLength)
{
	const auto poly6ConstantLaplacian = 945.0f / (32.0f * Tolerance<T>::getPI() * pow(effectLength, 9));
	return poly6ConstantLaplacian * (effectLength * effectLength - distance * distance)
		* (42.0f * distance * distance - 18.0f * effectLength * effectLength);
}

template<typename T, typename int DIM>
Vector3d<T> SPHKernel<T,DIM>::getSpikyKernelGradient(const Vector3d<T> &distanceVector, const float effectLength)
{
	const auto constant = 45.0f / (Math::Tolerance<T>::getPI() * pow(effectLength, 6));
	const auto distance = distanceVector.getLength();
	return distanceVector * constant * pow(effectLength - distance, 2) / distance;
}

template<typename T, typename int DIM>
float SPHKernel<T,DIM>::getViscosityKernelLaplacian(const T distance, const T effectLength)
{
	const auto constant = 45.0f / (Math::Tolerance<T>::getPI() * pow(effectLength, 6));
	return (effectLength - distance) * constant;
}

template<typename T, typename int DIM>
T SPHKernel<T,DIM>::getCubicSpline(const T q)
{
	const auto coe = T{ 3 } / Tolerance<T>::getTwoPI();
	if (q < 1) {
		return coe * (T{ 2 } / T{ 3 }-q*q + T{ 0.5 }*q*q*q);
	}
	else if (q < 2) {
		return coe * (std::pow(2 - q, 3) / T{ 6 });
	}
	else {
		return 0;
	}
}

template<typename T, typename int DIM>
T SPHKernel<T,DIM>::getCubicSpline(const Vector3d<T>& v, const T effectLength)
{
	const auto q = v.getLength() / effectLength;
	const auto numerator = getCubicSpline(q);
	const auto denominator = std::pow(effectLength, DIM);
	return numerator / denominator;
}

template<typename T, typename int DIM>
T SPHKernel<T, DIM>::getCubicSpline(const Vector3d<T>& v, const Matrix3d<T>& m)
{
	const auto det = m.getDeterminant();
	const auto vv = v * m;
	const auto q = vv.getLength();
	return det * getCubicSpline(q);
}

template class SPHKernel<float>;
