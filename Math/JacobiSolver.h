#ifndef __CRYSTAL_MATH_JACOBI_SOLVER_H__
#define __CRYSTAL_MATH_JACOBI_SOLVER_H__

#include "Matrix.h"

namespace Crystal {
	namespace Math {

template<typename int ROW, typename int COLUMN, typename T>
class JacobiSolver
{
public:
	JacobiSolver(const Matrix<ROW, COLUMN, T>& matrix) :
		matrix(matrix)
	{}

	T getMaxvalue(int *p, int *q)
	{
		T max = fabs(matrix.get(0, 1));
		*p = 0;
		*q = 1;

		for (int i = 0; i < matrix.getRow(); i++) {
			for (int j = i + 1; j < matrix.getColumn(); j++) {
				T temp = fabs(matrix.get(i, j));

				if (temp > max) {
					max = temp;
					*p = i;
					*q = j;
				}
			}
		}

		return max;
	}

	Vector<ROW, T> solve(const T eps) {
		T max;
		int p;
		int q;
		do {
			if (!(max = getMaxvalue(&p, &q))) {
				break;
			}
			T app = matrix.get(p, p);
			T apq = matrix.get(p, q);
			T aqq = matrix.get(q, q);

			T alpha = (app - aqq) / T{ 2 };
			T beta = -apq;
			T gamma = fabs(alpha) / sqrt(alpha*alpha + beta * beta);

			T s = sqrt((T{ 1 } -gamma) / T{ 2 });
			T c = sqrt((T{ 1 } +gamma) / T{ 2 });
			if (alpha * beta < 0.0) {
				s = -s;
			}

			for (int i = 0; i < ROW; ++i) {
				T tmp = c * matrix.get(p, i) - s * matrix.get(q, i);
				matrix.set(q, i, s * matrix.get(p, i) + c * matrix.get(q, i));
				matrix.set(p, i, tmp);
			}

			for (int i = 0; i < ROW; ++i) {
				matrix.set(i, p, matrix.get(p, i));
				matrix.set(i, q, matrix.get(q, i));
			}

			matrix.set(p, p, c*c*app + s*s*aqq - 2 * s*c*apq);
			matrix.set(p, q, s*c*(app - aqq) + (c*c - s*s)*apq);
			matrix.set(q, p, s*c*(app - aqq) + (c*c - s*s)*apq);
			matrix.set(q, q, s*s*app + c*c*aqq + 2 * s*c*apq);

			for (int i = 0; i < ROW; ++i) {
				T tmp = c * eigenVector.get(i, p) - s*eigenVector.get(i, q);
				eigenVector.set(i, q, s*eigenVector.get(i, p) + c * eigenVector.get(i, q));
				eigenVector.set(i, p, tmp);
			}
		} while (max >= eps);
		Vector<ROW, T> v;
		for (int i = 0; i < ROW; ++i) {
			v.set(i, matrix.get(i, i));
		}
		return v;
	}

	Matrix<ROW, COLUMN, T> getOrthogonalMatrix() const { return eigenVector; }

private:
	Matrix<ROW, COLUMN, T> matrix;
	Matrix<ROW, COLUMN, T> eigenVector;
};

	}
}

#endif