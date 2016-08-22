#ifndef __CRYSTAL_GRAPHICS_MATERIAL_REPOSITORY_H__
#define __CRYSTAL_GRAPHICS_MATERIAL_REPOSITORY_H__

#include "Material.h"

namespace Crystal {
	namespace Graphics {

class MaterialRepository
{
public:
	MaterialRepository();

	~MaterialRepository();

	void clear();

	Material* create();

	Material* findById(const int id);

	std::list<Material*> get() const { return materials; }

private:
	std::list<Material*> materials;
	int nextId;
};
	}
}

#endif