#include "stdafx.h"
#include "Image.h"
#include "ImageRepository.h"

using namespace Crystal::Graphics;

ImageRepository::ImageRepository() :
	nextId(0)
{}

ImageRepository::~ImageRepository()
{
	clear();
}

void ImageRepository::clear()
{
	for (auto i : images) {
		delete i;
	}
	images.clear();
}

Image* ImageRepository::create(const int width, const int height)
{
	auto i = new Image(width, height, nextId++);
	images.push_back(i);
	return i;
}

Imagef* ImageRepository::createf(const int width, const int height)
{
	auto i = new Imagef(width, height, nextId++);
	images.push_back(i);
	return i;
}
