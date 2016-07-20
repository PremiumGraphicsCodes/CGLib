#include "stdafx.h"
#include "ISpaceHash.h"
#include <bitset>

using namespace Crystal::Math;
using namespace Crystal::Core;

ISpaceHash::ISpaceHash(const float divideLength, const int tableSize) :
	divideLength(divideLength),
	tableSize(tableSize)
{}

Index3d ISpaceHash::toIndex(const Vector3d<float>& pos)
{
	const int ix = static_cast<int>((pos.getX()) / divideLength);
	const int iy = static_cast<int>((pos.getY()) / divideLength);
	const int iz = static_cast<int>((pos.getZ()) / divideLength);
	return{ ix, iy, iz };
}

int ISpaceHash::toHash(const Vector3d<float>& pos)
{
	return toHash(toIndex(pos));
}

int ISpaceHash::toHash(const Index3d& index)
{
	std::bitset<32> x = index.getX() * p1;
	std::bitset<32> y = index.getY() * p2;
	std::bitset<32> z = index.getZ() * p3;
	//assert(x >= 0);
	//assert(y >= 0);
	//assert(z >= 0);
	const auto value = (x ^ y ^ z).to_ulong();
	return value % tableSize;
}