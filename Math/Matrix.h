#ifndef __CRYSTAL_MATH_MATRIX_H__
#define __CRYSTAL_MATH_MATRIX_H__

#include "Vector.h"

namespace Crystal {
	namespace Math {

template<typename int ROW, typename int COLUMN>
class Matrix
{

public:
	Matrix() {
		for (int i = 0; i < getColumn(); i++) {
			for (int j = 0; j < getRow(); j++) {
				if (i == j) {
					a[i*getRow() + j] = 1;
				}
				else {
					a[i*getRow() + j] = 0;
				}
			}
		}
	}

	Matrix<3, 3> qrDecomposition(double eps);

	Matrix<ROW, COLUMN> getNextAQ(const int nowsize);

	std::array<double, ROW*COLUMN> a;

	constexpr int getColumn() const { return COLUMN; }

	constexpr int getRow() const { return ROW; }

	void mult(const Vector<ROW>& v, const int size);

	void toTridiag();
};

	}
}
#endif