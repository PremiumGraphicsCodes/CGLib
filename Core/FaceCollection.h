#ifndef __CRYSTAL_CORE_FACE_COLLECTION_H__
#define __CRYSTAL_CORE_FACE_COLLECTION_H__

#include "Vertex.h"
#include "Face.h"

namespace Crystal {
	namespace Core {

class FaceCollection
{
public:
	FaceCollection();

	FaceCollection(const std::vector<Face*>& faces);

	FaceCollection(const std::list<Face*>& faces);

	~FaceCollection();

	void merge(FaceCollection& rhs);

	Face* create(Edge* v1, Edge* v2, Edge* v3);

	void clear();

	void cleaning();

	void renumber();

	void remove(Face* f);

	using iterator = std::list<Face*>::iterator;
	using const_iterator = std::list<Face*>::const_iterator;

	iterator begin() { return faces.begin(); }

	//iterator front() { return faces.front(); }

	const_iterator begin() const { return faces.begin(); }

	iterator end() { return faces.end(); }

	const_iterator end() const { return faces.end(); }

	size_t size() const { return faces.size(); }

//	Face* operator[](const int i) const { return faces[i]; }

	std::list<Face*> get() { return faces; }

	Face* findById(const int id);

	void add(Face* f);

private:
	int nextId;
	std::list<Face*> faces;

};

	}
}
#endif