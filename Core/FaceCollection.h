#ifndef __CRYSTAL_CORE_FACE_COLLECTION_H__
#define __CRYSTAL_CORE_FACE_COLLECTION_H__

namespace Crystal {
	namespace Core {
		class Edge;
		class Face;

class FaceCollection
{
public:
	FaceCollection();

	~FaceCollection();

	void clear();

	Face* create(Edge* e1, Edge* e2, Edge* e3);

private:
	int nextId;
	std::vector<Face*> faces;
};
	}
}

#endif