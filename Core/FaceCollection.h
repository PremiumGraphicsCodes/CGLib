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

	~FaceCollection();

	void merge(FaceCollection& rhs);

	Face* create(Vertex* v1, Vertex* v2, Vertex* v3);

	void clear();

	using iterator = std::vector<Face*>::iterator;
	using const_iterator = std::vector<Face*>::const_iterator;

	iterator begin() { return faces.begin(); }

	const_iterator begin() const { return faces.begin(); }

	iterator end() { return faces.end(); }

	const_iterator end() const { return faces.end(); }

	size_t size() const { return faces.size(); }

	Face* operator[](const int i) const { return faces[i]; }

private:
	std::vector<Face*> faces;

};

	}
}
#endif