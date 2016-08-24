#ifndef __CRYSTAL_CORE_FACE_REPOSITORY_H__
#define __CRYSTAL_CORE_FACE_REPOSITORY_H__

#include "Vertex.h"
#include "Face.h"

namespace Crystal {
	namespace Core {

class FaceRepository
{
public:
	FaceRepository();

	FaceRepository(const std::vector<Face*>& faces);

	FaceRepository(const std::list<Face*>& faces);

	~FaceRepository();

	void merge(FaceRepository& rhs);

	Face* create(HalfEdge* v1, HalfEdge* v2, HalfEdge* v3);

	void clear();

	void cleaning();

	void renumber();

	void remove(Face* f);

	using iterator = std::list<Face*>::iterator;
	using const_iterator = std::list<Face*>::const_iterator;

	iterator begin() { return faces.begin(); }

	const_iterator begin() const { return faces.begin(); }

	iterator end() { return faces.end(); }

	const_iterator end() const { return faces.end(); }

	size_t size() const { return faces.size(); }

	std::list<Face*> get() { return faces; }

	Face* findById(const int id);

	void add(Face* f);

	std::list<Face*> getDegenerateds();

private:
	int nextId;
	std::list<Face*> faces;

};

	}
}
#endif