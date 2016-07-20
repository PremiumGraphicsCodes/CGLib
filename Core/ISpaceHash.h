#ifndef __CRYSTAL_CORE_I_SPACE_HASH_H__
#define __CRYSTAL_CORE_I_SPACE_HASH_H__

#include "stdafx.h"

namespace Crystal {
	namespace Core {

class ISpaceHash
{
protected:
	ISpaceHash(const float divideLength, const int tableSize);

	int toHash(const Math::Vector3d<float>& pos);

	int toHash(const Math::Index3d& index);

	Math::Index3d toIndex(const Math::Vector3d<float>& pos);

	const float divideLength;

	const long int p1 = 73856093;
	const long int p2 = 19349663;
	const long int p3 = 83492791;
	const int tableSize;
};

	}
}

#endif