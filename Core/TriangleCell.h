#ifndef __CRYSTAL_CORE_TRIANGLE_CELL_H__
#define __CRYSTAL_CORE_TRIANGLE_CELL_H__

namespace Crystal {
	namespace Core {
		class Node;

class TriangleCell
{
public:
	TriangleCell(const std::array<Node*, 3>& nodes) :
		nodes(nodes)
	{}

	std::array<Node*, 3> get() const { return nodes; }

private:
	std::array<Node*, 3> nodes;
};

class QuadCell
{
public:
	QuadCell(const std::array<Node*, 4>& nodes) :
		nodes(nodes)
	{}

	std::array<TriangleCell, 2> toTriangleCells() const {
		TriangleCell c1({ nodes[0], nodes[1], nodes[2] });
		TriangleCell c2({ nodes[2], nodes[3], nodes[0] });
		return{ c1, c2 };
	}
private:
	std::array<Node*, 4> nodes;
};

	}
}

#endif