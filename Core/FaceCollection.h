#ifndef __CRYSTAL_CORE_FACE_COLLECTION_H__
#define __CRYSTAL_CORE_FACE_COLLECTION_H__

namespace Crystal {
	namespace Core {
		class Edge;
		class Face;

class FaceCollection_
{
public:
	FaceCollection_();

	~FaceCollection_();

	void clear();

	Face* create(Edge* e1, Edge* e2, Edge* e3);

	std::list<Face*> get() { return faces; }

	void merge(FaceCollection_& rhs);

private:
	int nextId;
	std::list<Face*> faces;
};
	}
}

#endif