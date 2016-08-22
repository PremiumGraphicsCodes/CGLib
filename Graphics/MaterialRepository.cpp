#include "stdafx.h"
#include "MaterialRepository.h"

using namespace Crystal::Graphics;

MaterialRepository::MaterialRepository() :
	nextId(0)
{}

MaterialRepository::~MaterialRepository()
{
	clear();
}

void MaterialRepository::clear()
{
	for (auto m : materials) {
		delete m;
	}
	materials.clear();
}

Material* MaterialRepository::create()
{
	auto m = new Material(nextId++);
	this->materials.push_back(m);
	return m;
}

Material* MaterialRepository::findById(const int id)
{
	for (auto m : materials) {
		if (m->getId() == id) {
			return m;
		}
	}
	return nullptr;
}
