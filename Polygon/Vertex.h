#ifndef __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__
#define __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__

#include "../Math/Vector3d.h"
#include "../Util/UnCopyable.h"
#include <list>
#include <array>

namespace Crystal {
	namespace Polygon {

class Vertex;
class TriangleFace;

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
	TriangleFace* f;
};


	}
}
#endif
