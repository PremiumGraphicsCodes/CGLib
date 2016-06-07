#ifndef __CRYSTAL_GRAPHICS_VISUAL_SURFACE_H__
#define __CRYSTAL_GRAPHICS_VISUAL_SURFACE_H__

#include "Material.h"
#include "../Core/Face.h"
#include "../Core/Surface.h"

namespace Crystal {
	namespace Graphics {

class FaceGroup
{
public:
private:
	std::vector<Core::Face*> faces;
	Material material;
};

class VisualSurface
{
public:
	VisualSurface(Core::Surface* surface, const Material& material) :
		surface(surface),
		material(material)
	{}

	Core::Surface* getSurface() const { return surface; }

	Material getMaterial() const { return material; }

	//void setGroup()
private:
	Core::Surface* surface;
	Material material;
	//std::vector<FaceGroup> groups;
};
	}
}

#endif