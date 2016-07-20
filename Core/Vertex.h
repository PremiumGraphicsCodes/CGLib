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
class Face;
class Edge;

class Vertex : public Math::Point3d<float>
{
public:
	Vertex(const Math::Point3d<float>& point, const unsigned int id = -1);

	Vertex(const Math::Vector3d<float>& position, const unsigned int id = -1);

	Vertex(const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal, const unsigned int id = -1);

	Vertex(const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal, const Math::Vector2d<float>& texCoord, const unsigned int id = -1);

	void addIn(Edge* e) {
		if (e) {
			this->inEdges.push_back(e);
		}
	}

	void addOut(Edge* e) {
		if (e) {
			this->outEdges.push_back(e);
		}
	}

	Vertex* clone();

	void setId(const int id) { this->id = id; }

	unsigned int getId() const { return id; }

	float calculateCollapseCost();

	std::list<Vertex*> getNeighbors() const;

	std::list<Vertex*> getNeighbors(const float length) const;

	std::list<Edge*> getInEdges() const { return inEdges; }

	std::list<Edge*> getOutEdges() const { return outEdges; }

	void merge(Vertex* rhs);

	bool isIsolated() {
		return inEdges.empty() && outEdges.empty();
	}

private:
	unsigned int id;
	std::list<Edge*> inEdges;
	std::list<Edge*> outEdges;
	//std::list<Face*> faces;
};

	}
}
#endif
