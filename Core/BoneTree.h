#ifndef __CRYSTAL_POLYGON_BONE_TREE_H__
#define __CRYSTAL_POLYGON_BONE_TREE_H__

#include <map>

namespace Crystal {
	namespace Core {
		class Bone;

class BoneTree
{
public:
	BoneTree() {}

	void add(Bone* parent, Bone* child);

private:
	std::multimap<Bone*, Bone*> map;
};
	}
}

#endif