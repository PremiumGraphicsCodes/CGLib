#include "stdafx.h"
#include "BoneTree.h"

using namespace Crystal::Core;

void BoneTree::add(Bone* parent, Bone* child)
{
	map.insert( std::make_pair( parent, child ) );
}
