#ifndef __CRYSTAL_MATH_ELLIPSOID_H__
#define __CRYSTAL_MATH_ELLIPSOID_H__

#include "Vector3d.h"
#include "Angle.h"
#include "Quaternion.h"
#include "IPrimitive3d.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class Curve3d;

		template<typename T>
		class Ellipsoid : public IPrimitive3d<T>
		{
		public:
			Ellipsoid();

			Ellipsoid(const Vector3d<T>& center, const T radius);

			Ellipsoid(const Vector3d<T>& center, const Vector3d<T>& radii);

			Ellipsoid(const Vector3d<T>& center, const Vector3d<T>& radii, const Quaternion<T>& orientation);

			T getVolume() const;

			Vector3d<T> getPosition(const Angle<T> u, const Angle<T> v) const;

			Vector3d<T> getRadii() const { return radii; }

			Curve3d<T> toCurve3d(const int uNum, const int vNum) const;

			Matrix3d<T> getScalingMatrix() const override;

		private:
			Vector3d<T> radii;
		};
	}
}

#endif