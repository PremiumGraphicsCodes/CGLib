#ifndef __CRYSTAL_SHADER_I__TEXTURE_H__
#define __CRYSTAL_SHADER_I__TEXTURE_H__

#include "GLee.h"

class ITexture
{
public:
	ITexture(const int id = 0) :
		id(id)
	{}

	virtual ~ITexture() {
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


#endif