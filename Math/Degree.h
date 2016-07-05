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

			Degree<T> operator-() const { return Degree<T>(-deg); }

			Degree<T> operator-(const Degree<T>& rhs) const { return Degree<T>(deg - rhs.deg); }

			Degree<T> operator+(const Degree<T>& rhs) const { return Degree<T>(deg + rhs.deg); }

			Degree<T> operator*(const T rhs) const { return Degree<T>(deg * rhs); }

			Degree<T> operator/(const T rhs) const { return Degree<T>(deg / rhs); }

			void operator+=(const Degree<T>& rhs) { this->deg += rhs.deg; }


		private:
			T deg;
		};
	}
}

#endif