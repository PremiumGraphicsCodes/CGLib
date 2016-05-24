#ifndef __CRYSTAL_MATH_VECTOR_H__
#define __CRYSTAL_MATH_VECTOR_H__

#include <array>

namespace Crystal {
	namespace Math {

template<typename int DIM, typename T>
class Vector
{
public:
	Vector() {
		v.fill(0);
	}

	Vector(const std::array<T, DIM>& v) :v(v)
	{
	}


	void set(int pos, T val) { this->v[pos] = val; }

	T operator[](int i) const { return v[i]; }

	std::array<T, DIM> v;

	T getHouseholder() {
		T norm = sqrt(this->getInnerProduct(*this));

		if (norm) {
			if (v[0] < 0) {
				norm = -norm;
			}
			v[0] += norm;

			T weight = 1 / (sqrt(2 * norm*v[0]));

			for (int i = 0; i< v.size(); i++) {
				v[i] *= weight;
			}
		}

		return -norm;
	}

	T getInnerProduct(const Vector<DIM,T>& vector2) {
		T sum = 0.0;
		for (size_t i = 0; i< DIM; i++) {
			sum += v[i] * vector2.v[i];
		}
		return sum;
	}

	constexpr int getDim() const { return DIM; }
};

	}
}

#endif