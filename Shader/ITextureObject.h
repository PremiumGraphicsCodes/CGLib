#ifndef __CRYSTAL_SHADER_I_TEXTURE_OBJECT_H__
#define __CRYSTAL_SHADER_I_TEXTURE_OBJECT_H__

#include "GLee.h"

namespace Crystal {
	namespace Shader {

class ITextureObject
{
public:
	ITextureObject(const int id = 0) :
		id(id)
	{}

	virtual ~ITextureObject() {
	}

	virtual void bind() const = 0;

	virtual void unbind() const = 0;

	int getId() const { return id; }

	GLuint getTexHandle() const { return texHandle; }

	int getWidth() const { return width; }

	int getHeight() const { return height; }


protected:
	int id;
	GLuint texHandle;
	int width;
	int height;

};

	}
}

#endif