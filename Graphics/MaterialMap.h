#ifndef __CRYSTAL_GRAPHICS_MATERIAL_MAP_H__
#define __CRYSTAL_GRAPHICS_MATERIAL_MAP_H__

#include "Material.h"

namespace Crystal {
	namespace Graphics {

class MaterialMap
{
public:
	MaterialMap(Material material, unsigned int startFaceIndex, unsigned int endFaceIndex) :
		material(material),
		startFaceIndex(startFaceIndex),
		endFaceIndex(endFaceIndex)
	{
	}

	Material getMaterial() const { return material; }

	unsigned int getStartFaceIndex() const { return startFaceIndex; }

	unsigned int getEndFaceIndex() const { return endFaceIndex; }

private:
	Material material;
	unsigned int startFaceIndex;
	unsigned int endFaceIndex;
};

	}
}

#endif