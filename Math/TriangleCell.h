#ifndef __CRYSTAL_MATH_TRIANGLE_CELL_H__
#define __CRYSTAL_MATH_TRIANGLE_CELL_H__

#include <array>

namespace Crystal {
	namespace Math {
		template<typename T>
		class Point3d;

template<typename T>
class TriangleCell
{
public:

	TriangleCell(Point3d<T>* p1, Point3d<T>* p2, Point3d<T>* p3)
	{
		nodes[0] = p1;
		nodes[1] = p2;
		nodes[2] = p3;
	}

	TriangleCell(const std::array<Point3d<T>*, 3>& nodes) :
		nodes(nodes)
	{}

	std::array<Point3d<T>*, 3> get() const { return nodes; }

private:
	std::array<Point3d<T>*, 3> nodes;
};

template<typename T>
class QuadCell
{
public:
	QuadCell(const std::array<Point3d<T>*, 4>& nodes) :
		nodes(nodes)
	{}

	std::array<TriangleCell<T>, 2> toTriangleCells() const {
		TriangleCell<T> c1({ nodes[0], nodes[1], nodes[2] });
		TriangleCell<T> c2({ nodes[2], nodes[3], nodes[0] });
		return{ c1, c2 };
	}
private:
	std::array<Point3d<T>*, 3> nodes;
};

	}
}

#endif