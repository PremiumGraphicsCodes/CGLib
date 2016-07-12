#ifndef __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__
#define __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__

#include "../Math/Point3d.h"
#include "../Math/Vector3d.h"
#include "../Math/Matrix4d.h"
#include "../Util/UnCopyable.h"
#include <list>
#include <array>

namespace Crystal {
	namespace Core {

class Vertex;
class TriFace;

class Vertex : public Math::Point3d<float>
{
public:
	Vertex(const Math::Vector3d<float>& position, const unsigned int id );

	Vertex(const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal, const unsigned int id);

	Vertex(const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal, const Math::Vector2d<float>& texCoord, const unsigned int id);

	//void normalize(const Vertex& rhs);

	void addFace(TriFace* f) {
		this->faces.push_back( f );
		this->faces.sort();
		this->faces.unique();
	}

	std::list< TriFace* > getFaces() const { return faces; }

	//void transform(const Math::Matrix4d<float>& matrix);

	Vertex* clone();

	void setId(const int id) { this->id = id; }

	unsigned int getId() const { return id; }
	unsigned int id;

private:
	std::list<TriFace*> faces;
};

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
