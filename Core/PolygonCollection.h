#ifndef __CRYSTAL_CORE_POLYGON_COLLECTION_H__
#define __CRYSTAL_CORE_POLYGON_COLLECTION_H__

#include "PolygonMesh.h"

namespace Crystal {
	namespace Core {

class PolygonCollection
{
public:
	PolygonCollection() :
		nextId(0)
	{}

	void clear() {
			for (auto p : polygons) {
				delete p;
			}
			polygons.clear();
			nextId = 0;
	}

	void add(PolygonMesh* polygon) {
		polygons.push_back(polygon);
	}

	PolygonMesh* findById(const int id) {
		for (auto p : polygons) {
			if (p->getId() == id) {
				return p;
			}
		}
		return nullptr;
	}

	std::list<PolygonMesh*> getPolygons() const { return polygons; }

	void cleaning()
	{
		//removeOverlappedVertices();
		//polygons.cleaning();
	}

	void renumber()
	{
		//faces.cleaning();
	}


private:
	std::list<PolygonMesh*> polygons;
	int nextId;
};
	}
}

#endif