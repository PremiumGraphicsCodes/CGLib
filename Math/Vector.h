#ifndef __CRYSTAL_MATH_VECTOR_H__
#define __CRYSTAL_MATH_VECTOR_H__

#include <array>

namespace Crystal {
	namespace Math {

template<typename int DIM>
class Vector
{
public:
	Vector() {
		v.fill(0);
	}

	explicit Vector(const std::array<double, DIM>& v) :v(v)
	{
	}


	void set(int pos, double val) { this->v[pos] = val; }

	std::array<double, DIM> v;

	double getHouseholder() {
		double norm = sqrt(this->getDotProduct(*this));

		if (norm) {
			if (v[0] < 0) {
				norm = -norm;
			}
			v[0] += norm;

			double weight = 1 / (sqrt(2 * norm*v[0]));

			for (int i = 0; i< v.size(); i++) {
				v[i] *= weight;
			}
		}

		return -norm;
	}

	double getDotProduct(const Vector<DIM>& vector2) {
		double sum = 0.0;
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