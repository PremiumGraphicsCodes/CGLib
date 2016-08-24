#include "stdafx.h"
#include "TextureObjectRepository.h"
#include "TextureObject.h"
#include "DepthTextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TextureObjectRepository::TextureObjectRepository() :
	nextId(0)
{
}

TextureObjectRepository::~TextureObjectRepository()
{
	clear();
}

void TextureObjectRepository::clear()
{
	for (auto tex : textures) {
		delete tex;
	}
	textures.clear();
	nextId = 0;
}

TextureObject* TextureObjectRepository::create(const Image& image)
{
	auto tex = new TextureObject(image, nextId++);
	textures.push_back(tex);
	return tex;
}

TextureObject* TextureObjectRepository::create(const Imagef& image)
{
	auto tex = new TextureObject(image, nextId++);
	textures.push_back(tex);
	return tex;
}


TextureObject* TextureObjectRepository::create(Image* image)
{
	if (has(image)) {
		return find(image);
	}
	auto tex = new TextureObject(*image, nextId++);
	textures.push_back(tex);
	imageTexMap[image] = tex;
	return tex;
}

TextureObject* TextureObjectRepository::create(Imagef* image)
{
	if (has(image)) {
		return find(image);
	}

	auto tex = new TextureObject(*image, nextId++);
	textures.push_back(tex);
	imageTexMap[image] = tex;
	return tex;
}

DepthTextureObject* TextureObjectRepository::createDepth(const Imagef& image)
{
	auto tex = new DepthTextureObject(image, nextId++);
	textures.push_back(tex);
	return tex;
}

bool TextureObjectRepository::has(IImage* image)
{
	return imageTexMap.find(image) != imageTexMap.end();
}


TextureObject* TextureObjectRepository::find(IImage* image)
{
	if (has(image)){
		return imageTexMap[image];
	}
	return nullptr;
}

void TextureObjectRepository::update(Image* image)
{
	assert(has(image));
	find(image)->send(*image);
}

void TextureObjectRepository::update(Imagef* image)
{
	assert(has(image));
	find(image)->send(*image);
}
