#include "BoneTree.h"

using namespace Crystal::Polygon;

void BoneTree::add(Bone* parent, Bone* child)
{
	map.insert( std::make_pair( parent, child ) );
}
