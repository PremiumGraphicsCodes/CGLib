#ifndef __CRYSTAL_CORE_VERTEX_COLLECTION_H__
#define __CRYSTAL_CORE_VERTEX_COLLECTION_H__

#include "Vertex.h"

namespace Crystal {
	namespace Core {

class VertexCollection
{
public:
	VertexCollection();

	VertexCollection(const std::vector<Vertex*>& vertices);

	~VertexCollection();

	Vertex* create(Math::Vector3d<float> position, Math::Vector3d<float> normal = Math::Vector3d<float>(), Math::Vector2d<float> texCoord = Math::Vector2d<float>());

	VertexCollection clone();

	void merge(VertexCollection& rhs);

	void clear();

	bool hasVertex(Vertex* v);

	void sort();

	void cleaning();

	Vertex* operator[](int index) const { return vertices[index]; }

	using iterator = std::vector<Vertex*>::iterator;
	using const_iterator = std::vector<Vertex*>::const_iterator;

	iterator begin() { return vertices.begin(); }

	const_iterator begin() const { return vertices.begin(); }

	iterator end() { return vertices.end(); }

	const_iterator end() const { return vertices.end(); }

	size_t size() const { return vertices.size(); }

private:
	std::vector<Vertex*> vertices;
	unsigned int nextId;
};

	}
}

#endif