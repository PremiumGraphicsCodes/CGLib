#include "OBJFileLoader.h"

using namespace Crystal::Graphics;
using namespace Crystal::IO;

bool OBJFileLoader::load(const File& file)
{
	objFile.read(file);
	auto polygon = objFile.toPolygonObject();
	visualPolygon = Graphics::VisualPolygon(polygon);
	auto libs = objFile.getMTLLibs();
	for (auto lib : libs) {
		std::string mtlFileName = file.getFolerPath() + lib;
		MTLFile mtlFile;
		mtlFile.read(mtlFileName);
		mtlFiles.push_back(mtlFile);
		/*
		const auto materials = objFile.getMaterials();
		const auto& names = materials.getNames();
		for (auto& n : names) {
			auto faces = materials.getFaces(n);
			faces.size();
			auto mat = mtlFile.find(n);
			auto mat2 = mat.toMaterial();
			MaterialMap mm();
			visualPolygon.setMaterial()
			for (auto& f : faces) {
				f.
			}
		}
		/*
		MaterialMap mm;

		visualPolygon.setMaterial()
			auto start = materials.lower_bound(lib);
		auto end = materials.upper_bound(lib);
		for (auto iter = start; iter != end; ++iter) {
			if (iter->first == start) {
			}
		}
		*/
	}
	return true;
}