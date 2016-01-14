#ifndef __CRYSTAL_MATH_TOLERANCE_H__
#define __CRYSTAL_MATH_TOLERANCE_H__

#include <cmath>

namespace Crystal {
	namespace Math {

template<typename T>
class Tolerance : final
{
};

template<>
class Tolerance < float > final
{
public:
	static float getLooseTolerance() {
		return 1.0e-9f;
	}

	static float getStrictTolerance() {
		return 1.0e-18f;
	}

	static bool isEqualLoosely(const float x) { return ::fabs(x) < getLooseTolerance(); }

	static bool isEqualLoosely(const float x, const float y) { return ::fabs(x - y) < getLooseTolerance(); }

	static bool isEqualStrictly(const float x) { return ::fabs(x) < getStrictTolerance(); }

	static bool isEqualStrictly(const float x, const float y) { return ::fabs(x - y) < getStrictTolerance(); }

	static float getHalfPI() { return 0.5f * getPI(); }

	static float getPI() { return 3.14159265359f; }

	static float getTwoPI() { return 2.0f * getPI(); }
};

template<>
class Tolerance < double > final
{
public:
	static double getLooseTolerance() {
		return 1.0e-9;
	}

	static double getStrictTolerance() {
		return 1.0e-18;
	}

	static bool isEqualLoosely(const double x) { return ::fabs(x) < getLooseTolerance(); }

	static bool isEqualLoosely(const double x, const double y) { return ::fabs(x - y) < getLooseTolerance(); }

	static bool isEqualStrictly(const double x) { return ::fabs(x) < getStrictTolerance(); }

	static bool isEqualStrictly(const double x, const double y) { return ::fabs(x - y) < getStrictTolerance(); }

	static double getHalfPI() { return 0.5 * getPI(); }

	static double getPI() { return 3.141592653589793238462643383279; }

	static double getTwoPI() { return 2.0 * getPI(); }

};


/*
static bool isEqualLoosely(double x) { return ::fabs(x) < getLooseTolerance(); }

static bool isEqualLoosely(double x, double y) { return ::fabs(x - y) < getLooseTolerance(); }

static bool isEqualStrictly(double x) { return ::fabs(x) < getStrictTolerance(); }

static bool isEqualStrictly(double x, double y) { return ::fabs(x - y) < getStrictTolerance(); }

static float getPI() { return 3.14159265359f; }

static float getTwoPI() { return 2.0f * getPI(); }

static double getPrecisePI() { return 3.141592653589793238462643383279; }
*/

	}
}

#endif