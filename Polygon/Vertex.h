#ifndef __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__
#define __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__

#include "../Math/Vector3d.h"
#include "../Math/Matrix4d.h"
#include "../Util/UnCopyable.h"
#include <list>
#include <array>

namespace Crystal {
	namespace Polygon {

class Vertex;
class Face;

class Vertex
{
public:
	Vertex(const unsigned int id, const Math::Vector3d<float>& position);

	Vertex(const unsigned int id, const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal);

	Vertex(const unsigned int id, const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal, const Math::Vector3d<float>& texCoord);

	Math::Vector3d<float> getPosition() const { return position; }

	Math::Vector3d<float> getNormal() const { return normal; }

	Math::Vector3d<float> getTexCoord() const { return texCoord; }

	void normalize(const Vertex& rhs);

	void setFace(Face* f) { this->f = f; }

	Face* getFace() const { return f; }

	void transform(const Math::Matrix4d<float>& matrix);

	Vertex* clone();

	unsigned int getId() const { return id; }
	unsigned int id;

private:
	Math::Vector3d<float> position;
	Math::Vector3d<float> normal;
	Math::Vector3d<float> texCoord;

	Face* f;
};

class VertexCollection
{
public:
	VertexCollection();

	VertexCollection(const std::vector<Vertex*>& vertices);

	~VertexCollection();

	Vertex* create(Math::Vector3d<float> position, Math::Vector3d<float> normal = Math::Vector3d<float>(), Math::Vector3d<float> texCoord = Math::Vector3d<float>());

	VertexCollection clone();

	void merge(VertexCollection& rhs);

	void clear();

	bool hasVertex(Vertex* v);

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
	unsigned int nextId;
};

	}
}
#endif
