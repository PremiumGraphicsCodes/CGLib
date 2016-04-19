#ifndef __CRYSTAL_SHADER_TEXTURE_H__
#define __CRYSTAL_SHADER_TEXTURE_H__

#include "GLee.h"
#include "../Graphics/Image.h"

namespace Crystal {
	namespace Shader {

class Texture
{
public:
	Texture(const int id = 0) :
		id(id)
	{}

	Texture(const Graphics::Image& image, const int id = 0);

	bool create(const Graphics::Image& image, const int id = 0);

	~Texture() { unbind(); }

	void bind() const;

	void unbind() const;

	int getId() const { return id; }

	GLuint getTexHandle() const { return texHandle; }

	int getWidth() const { return width; }

	int getHeight() const { return height; }

private:
	int id;
	GLuint texHandle;
	int width;
	int height;
};

class Texturef
{
public:
	Texturef(const int id = 0) :
		id(id)
	{}

	Texturef(const Graphics::Imagef& image, const int id = 0);

	bool create(const Graphics::Imagef& image, const int id = 0);

	~Texturef() { unbind(); }

	void bind() const;

	void unbind() const;

	int getId() const { return id; }

	GLuint getTexHandle() const { return texHandle; }

	int getWidth() const { return width; }

	int getHeight() const { return height; }

private:
	int id;
	GLuint texHandle;
	int width;
	int height;
};


	}
}

#endif