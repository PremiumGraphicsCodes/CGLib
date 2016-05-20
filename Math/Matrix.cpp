#include "Matrix.h"

using namespace Crystal::Math;

namespace {
	double GetEigenvalue22(double a11, double a12, double a21, double a22)
	{
		const double b = a22 + a11;
		double det = b*b - 4 * (a22*a11 - a12*a21);

		if (det < 0) {
			det = 0;
		}
		const double eig1 = (b + sqrt(det)) / 2;
		const double eig2 = (b - sqrt(det)) / 2;

		if (fabs(a22 - eig1) < fabs(a22 - eig2)) {
			return eig1;
		}
		else {
			return eig2;
		}
	}
}


void Matrix<3, 3>::toTridiag()
{
	Vector<3> v;
	int i, j;
	double tmp;

	int currentSize = 3;
	for (i = 0; i<getRow() - 2; i++) {
		//v.pop_back();
		currentSize--;
		for (j = i + 1; j<getRow(); j++) {
			//v[j - i - 1] = a[i*getWidth() + j];
			v.set(j - i - 1, a[i*getRow() + j]);
		}
		if (!(tmp = v.getHouseholder())) {
			continue;
		}

		this->mult(v, currentSize);

		a[i*getRow() + i + 1] = a[(i + 1)*getRow() + i] = tmp;
		for (j = i + 2; j<getRow(); j++) {
			a[i*getRow() + j] = a[j*getRow() + i] = 0;
		}


	}
}

template<typename int ROW, typename int COLUMN>
void Matrix<ROW, COLUMN>::mult(const Vector<ROW>& v, int size)
{
	Vector<3> g;

	size_t offset = ROW - size;

	for (size_t i = offset; i < ROW; i++) {
		g.v[i - offset] = 0;
		for (size_t j = offset; j<ROW; j++) {
			g.v[i - offset] += a[i*ROW + j] * v.v[j - offset];
		}
	}

	const double tmp = g.getDotProduct(v);

	for (int j = 0; j<g.v.size(); j++) {
		g.v[j] = 2 * (g.v[j] - v.v[j] * tmp);
	}
	for (size_t i = offset; i< ROW; i++) {
		for (size_t j = offset; j<ROW; j++) {
			a[i*ROW + j] -= (v.v[i - offset] * g.v[j - offset] + g.v[i - offset] * v.v[j - offset]);
		}
	}
}

//template<typename int ROW, typename int COLUMN>
Matrix<3,3> Matrix<3, 3>::qrDecomposition(double eps)
{
	Matrix<3,3> q;
	Vector<3> v;

	toTridiag();

	int nowsize = getRow();

	while (nowsize > 1) {
		if (fabs(a[(nowsize - 1)* ROW + nowsize - 2]) < eps) {
			nowsize--;
			continue;
		}

		const double u = ::GetEigenvalue22(
			a[(nowsize - 2)*getRow() + nowsize - 2],
			a[(nowsize - 2)*getRow() + nowsize - 1],
			a[(nowsize - 1)*getRow() + nowsize - 2],
			a[(nowsize - 1)*getRow() + nowsize - 1]);

		for (int i = 0; i<nowsize; i++) {
			a[i*getRow() + i] -= u;
		}

		q = getNextAQ(nowsize);

		for (int i = 0; i<nowsize; i++) {
			for (int j = 0; j<nowsize; j++) {
				double sum = 0;
				for (int k = i; k<nowsize; k++) {
					sum += a[i* ROW + k] * q.a[k* ROW + j];
				}
				v.v[j] = sum;
			}
			for (int j = 0; j<nowsize; j++) {
				a[i*ROW + j] = v.v[j];
			}
		}

		for (int i = 0; i<nowsize; i++) {
			a[i*ROW + i] += u;
		}
	}
	return q;
}



template<typename int ROW, typename int COLUMN>
Matrix<ROW, COLUMN> Matrix<ROW, COLUMN>::getNextAQ(const int nowsize)
{
	Matrix<ROW, COLUMN> q;
	for (int i = 0; i<nowsize - 1; i++) {
		double alpha = sqrt(a[i*getRow() + i] * a[i*getRow() + i] + a[(i + 1)*getRow() + i] * a[(i + 1)*getRow() + i]);
		double s = a[(i + 1)*getRow() + i] / alpha;
		double c = a[i*getRow() + i] / alpha;

		for (int j = i + 1; j<nowsize; j++) {
			double temp = -a[i*getRow() + j] * s + a[(i + 1)*getRow() + j] * c;
			a[i*getRow() + j] = a[i*getRow() + j] * c + a[(i + 1)*getRow() + j] * s;
			a[(i + 1)*getRow() + j] = temp;
		}

		for (int j = 0; j<nowsize; j++) {
			double temp = -q.a[j*q.getRow() + i] * s + q.a[j*q.getRow() + i + 1] * c;
			q.a[j*getRow() + i] = q.a[j*q.getRow() + i] * c + q.a[j*q.getRow() + i + 1] * s;
			q.a[j*getRow() + i + 1] = temp;
		}
		a[i*getRow() + i] = alpha;
		a[(i + 1)*getRow() + i] = 0;
	}
	return q;
}
