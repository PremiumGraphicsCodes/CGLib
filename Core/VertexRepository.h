#ifndef __CRYSTAL_CORE_VERTEX_REPOSITORY_H__
#define __CRYSTAL_CORE_VERTEX_REPOSITORY_H__

#include "Vertex.h"
#include "vector"

namespace Crystal {
	namespace Core {

class VertexRepository
{
public:
	VertexRepository();

	VertexRepository(const std::vector<Vertex*>& vertices);

	VertexRepository(const std::list<Vertex*>& vertices);

	~VertexRepository();

	Vertex* create(Math::Vector3d<float> position, Math::Vector3d<float> normal = Math::Vector3d<float>(), Math::Vector2d<float> texCoord = Math::Vector2d<float>());

	Vertex* create(const Math::Point3d<float>& point);

	Vertex* findById(const int id) const;

	VertexRepository clone();

	void merge(VertexRepository& rhs);

	void clear();

	bool hasVertex(Vertex* v);

	void sort();

	void renumber();

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