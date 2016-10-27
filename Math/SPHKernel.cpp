#include "SPHKernel.h"

using namespace Crystal::Math;

template<typename T, typename int DIM>
T SPHKernel<T,DIM>::getPoly6Kernel(const T distance, const T effectLength)
{
	if (distance > effectLength) {
		return T{ 0 };
	}
	const auto poly6Constant = 315.0f / (64.0f * Math::Tolerance<T>::getPI() * pow(effectLength, 9));
	return poly6Constant * pow(effectLength * effectLength - distance * distance, 3);
}

template<typename T, typename int DIM>
Vector3d<T> SPHKernel<T,DIM>::getPoly6KernelGradient(const Vector3d<T>& distanceVector, const T effectLength)
{
	const auto distance = distanceVector.getLength();
	if (distance > effectLength) {
		return Vector3d<T>(0,0,0);
	}
	const auto poly6ConstantGradient = 945.0f / (32.0f * Tolerance<T>::getPI() * pow(effectLength, 9));
	const auto factor = poly6ConstantGradient * pow(effectLength * effectLength - distance * distance, 2);
	return distanceVector * factor;
}

template<typename T, typename int DIM>
T SPHKernel<T,DIM>::getPoly6KernelLaplacian(const T distance, const T effectLength)
{
	if (distance > effectLength) {
		return T{ 0 };
	}
	const auto poly6ConstantLaplacian = 945.0f / (32.0f * Tolerance<T>::getPI() * pow(effectLength, 9));
	return poly6ConstantLaplacian * (effectLength * effectLength - distance * distance)
		* (42.0f * distance * distance - 18.0f * effectLength * effectLength);
}

template<typename T, typename int DIM>
Vector3d<T> SPHKernel<T,DIM>::getSpikyKernelGradient(const Vector3d<T> &distanceVector, const T effectLength)
{
	const auto distance = distanceVector.getLength();
	if (distance > effectLength) {
		return Vector3d<T>(0, 0, 0);
	}
	const auto constant = 45.0f / (Math::Tolerance<T>::getPI() * pow(effectLength, 6));
	return distanceVector * constant * pow(effectLength - distance, 2) / distance;
}

template<typename T, typename int DIM>
T SPHKernel<T,DIM>::getViscosityKernelLaplacian(const T distance, const T effectLength)
{
	if (distance > effectLength) {
		return T{ 0 };
	}
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
T SPHKernel<T, DIM>::getCubicSpline(const T distance, const T effectRadius)
{
	const auto q = distance * 2 / (effectRadius);
	return getCubicSpline(q);
}

template<typename T, typename int DIM>
Vector3d<T> SPHKernel<T,DIM>::getCubicSplineGradient(const Vector3d<T>& distanceVector)
{
	const auto coe = T{ 3 } / Tolerance<T>::getTwoPI();
	const auto length = distanceVector.getLength();
	const auto lengthSquared = distanceVector.getLengthSquared();
	if (Tolerance<T>::isEqualStrictly(length)) {
		return Vector3d<T>(0, 0, 0);
	}
	else if (length < 1) {
		const auto var = -T{ 2 } *length + T{ 1.5 } * lengthSquared;
		return coe * var * distanceVector.normalized();
	}
	else if (length < 2) {
		const auto var = -T{ 0.5 } *std::pow( T(2.0 - length), 2 );
		return coe * var * distanceVector.normalized();
	}
	else {
		return Vector3d<T>(0,0,0);
	}
}

template<typename T, typename int DIM>
Vector3d<T> SPHKernel<T, DIM>::getCubicSplineGradient(const Vector3d<T>& distanceVector, const T effectRadius)
{
	const auto scale = distanceVector.getLength() * T { 2 } / effectRadius;
	return getCubicSplineGradient(distanceVector.scaled(scale));
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
	const auto q = vv.getLength() * 2;
	return det * getCubicSpline(q);
}

template class SPHKernel<float>;
