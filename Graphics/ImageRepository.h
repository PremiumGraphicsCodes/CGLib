#ifndef __CRYSTAL_GRAPHICS_IMAGE_REPOSITORY_H__
#define __CRYSTAL_GRAPHICS_IMAGE_REPOSITORY_H__

#include "Image.h"
#include "../Util/UnCopyable.h"
#include <list>

namespace Crystal {
	namespace Graphics {

class ImageRepository : private UnCopyable
{
public:
	ImageRepository();

	~ImageRepository();

	void clear();

	Image* create(const int width, const int height);

	Imagef* createf(const int width, const int height);

private:
	std::list<IImage*> images;
	int nextId;
};
	}
}

#endif