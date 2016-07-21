#ifndef __CRYSTAL_CORE_VERTEX_COLLECTION_H__
#define __CRYSTAL_CORE_VERTEX_COLLECTION_H__

#include "Vertex.h"
#include "vector"

namespace Crystal {
	namespace Core {

class VertexCollection
{
public:
	VertexCollection();

	VertexCollection(const std::vector<Vertex*>& vertices);

	VertexCollection(const std::list<Vertex*>& vertices);

	~VertexCollection();

	Vertex* create(Math::Vector3d<float> position, Math::Vector3d<float> normal = Math::Vector3d<float>(), Math::Vector2d<float> texCoord = Math::Vector2d<float>());

	Vertex* create(const Math::Point3d<float>& point);

	Vertex* findById(const int id) const;

	VertexCollection clone();

	void merge(VertexCollection& rhs);

	void clear();

	bool hasVertex(Vertex* v);

	void sort();

	void renumber();

	//Vertex* operator[](int index) const { return vertices[index]; }

	using iterator = std::list<Vertex*>::iterator;
	using const_iterator = std::list<Vertex*>::const_iterator;

	iterator begin() { return vertices.begin(); }

	const_iterator begin() const { return vertices.begin(); }

	iterator end() { return vertices.end(); }

	const_iterator end() const { return vertices.end(); }

	size_t size() const { return vertices.size(); }

	std::list<Vertex*> get() { return vertices; }

	void add(Vertex* v);

	void remove(Vertex* v);

	void cleaning();

	std::list<Vertex*> find(const Math::Vector3d<float>& position, const float effectLength);

	Vertex* findById(const int id);

private:
	std::list<Vertex*> vertices;
	unsigned int nextId;
};

	}
}

#endif