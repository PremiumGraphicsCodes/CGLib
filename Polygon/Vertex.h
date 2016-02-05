#ifndef __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__
#define __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__

#include "../Math/Vector3d.h"
#include "../Util/UnCopyable.h"
#include <list>
#include <array>

namespace Crystal {
	namespace Polygon {

class Vertex;
class Face;

class VectorId
{
public:
	VectorId(const Math::Vector3d<float>& vector, const int id) :
		vector(vector),
		id(id)
	{}

	Math::Vector3d<float> getVector() const { return vector; }

	int getId() const { return id; }

private:
	Math::Vector3d<float> vector;
	int id;
};

class VectorIdCollection
{
public:
	VectorIdCollection() :
		nextId(0)
	{}

	void clear() {
		for (auto p : positions) {
			delete p;
		}
		positions.clear();
		nextId = 0;
	}

	VectorId* get(const int index) const { return positions[index]; }


	size_t size() const { return positions.size(); }

	VectorId* create(const Math::Vector3d<float>& position)
	{
		auto v = new VectorId(position, nextId++);
		positions.push_back( v );
		return v;
	}

	using iterator = std::vector<VectorId*>::iterator;
	using const_iterator = std::vector<VectorId*>::const_iterator;

	iterator begin() { return positions.begin(); }

	const_iterator begin() const { return positions.begin(); }

	iterator end() { return positions.end(); }

	const_iterator end() const { return positions.end(); }

private:
	std::vector<VectorId*> positions;
	int nextId;
};

class Vertex
{
public:
	Vertex() :
		position(nullptr),
		normal(nullptr),
		texCoord(nullptr),
		id(-1)
	{}

	int id;

	VectorId* getPosition() { return position; }

	VectorId* getNormal() { return normal; }

	VectorId* getNormal() const { return normal; }

	int getId() const { return id; }

	VectorId* position;
	VectorId* normal;
	VectorId* texCoord;
	Face* f;
};

class VertexCollection
{
public:
	VertexCollection() :
		nextId(0)
	{}

	VertexCollection(const std::vector<Vertex*>& vertices) :
		vertices( vertices ),
		nextId(0)
	{}

	Vertex* create(VectorId* position, VectorId* normal = nullptr, VectorId* texCoord = nullptr);

	~VertexCollection() {
	}

	void clear() {
		for (auto v : vertices) {
			delete v;
		}
		vertices.clear();
	}

	bool hasVertex(Vertex* v) {
		return (std::find(vertices.begin(), vertices.end(), v) != vertices.end());
	}

	void sort();

	Vertex* operator[](int index) const{ return vertices[index]; }

	using iterator = std::vector<Vertex*>::iterator;
	using const_iterator = std::vector<Vertex*>::const_iterator;

	iterator begin() { return vertices.begin(); }

	const_iterator begin() const { return vertices.begin(); }

	iterator end() { return vertices.end(); }

	const_iterator end() const { return vertices.end(); }

	size_t size() const { return vertices.size(); }

private:
	std::vector<Vertex*> vertices;
	int nextId;
};

	}
}
#endif
