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

class Vertex : public Math::Point3d<float>
{
public:
	Vertex(const Math::Vector3d<float>& position, const unsigned int id );

	Vertex(const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal, const unsigned int id);

	Vertex(const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal, const Math::Vector2d<float>& texCoord, const unsigned int id);

	void addFace(Face* f) {
		this->faces.push_back( f );
		this->faces.sort();
		this->faces.unique();
	}

	std::list< Face* > getFaces() const { return faces; }

	Vertex* clone();

	void setId(const int id) { this->id = id; }

	unsigned int getId() const { return id; }

	float calculateCollapseCost();

	std::list<Vertex*> getNeighbors() const;

private:
	unsigned int id;
	std::list<Face*> faces;
};

	}
}
#endif
