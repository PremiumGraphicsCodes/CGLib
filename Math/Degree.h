#ifndef __CRYSTAL_MATH_DEGREE_H__
#define __CRYSTAL_MATH_DEGREE_H__

namespace Crystal {
	namespace Math {

		template<typename T>
		class Radian;

		template<typename T>
		class Degree
		{
		public:
			Degree();

			explicit Degree(const T deg);

			Radian<T> toRadian() const;

			T get() const { return deg; }

			bool equals(const Degree<T> rhs) const;

			bool operator==(const Degree<T> rhs) const;

			bool operator!=(const Degree<T> rhs) const;

		private:
			T deg;
		};
	}
}

#endif