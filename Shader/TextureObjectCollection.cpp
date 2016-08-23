#include "stdafx.h"
#include "TextureObjectCollection.h"
#include "TextureObject.h"
#include "DepthTextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

TextureObjectCollection::TextureObjectCollection() :
	nextId(0)
{
}

TextureObjectCollection::~TextureObjectCollection()
{
	clear();
}

void TextureObjectCollection::clear()
{
	for (auto tex : textures) {
		delete tex;
	}
	textures.clear();
	nextId = 0;
}

TextureObject* TextureObjectCollection::create(const Image& image)
{
	auto tex = new TextureObject(image, nextId++);
	textures.push_back(tex);
	return tex;
}

TextureObject* TextureObjectCollection::create(const Imagef& image)
{
	auto tex = new TextureObject(image, nextId++);
	textures.push_back(tex);
	return tex;
}


TextureObject* TextureObjectCollection::create(Image* image)
{
	if (has(image)) {
		return find(image);
	}
	auto tex = new TextureObject(*image, nextId++);
	textures.push_back(tex);
	imageTexMap[image] = tex;
	return tex;
}

TextureObject* TextureObjectCollection::create(Imagef* image)
{
	if (has(image)) {
		return find(image);
	}

	auto tex = new TextureObject(*image, nextId++);
	textures.push_back(tex);
	imageTexMap[image] = tex;
	return tex;
}

DepthTextureObject* TextureObjectCollection::createDepth(const Imagef& image)
{
	auto tex = new DepthTextureObject(image, nextId++);
	textures.push_back(tex);
	return tex;
}

bool TextureObjectCollection::has(IImage* image)
{
	return imageTexMap.find(image) != imageTexMap.end();
}


TextureObject* TextureObjectCollection::find(IImage* image)
{
	if (has(image)){
		return imageTexMap[image];
	}
	return nullptr;
}
