#ifndef __CRYSTAL_CORE_POLYGON_BUILDER_H__
#define __CRYSTAL_CORE_POLYGON_BUILDER_H_

namespace Crystal {
	namespace Core {
		class Vertex;
		class Face;
		class Edge;
		class Volume;
		class ParticleObject;
		class PolygonMesh;

class PolygonBuilder
{
public:
	PolygonBuilder() {}

	PolygonBuilder(const std::vector<Vertex*>& vertices) :
		vertices(vertices)
	{}

	PolygonBuilder(const std::vector<Vertex*>& vertices, const std::vector<Face*>& faces, const std::vector<Edge*>& edges);

	PolygonBuilder(const Volume& volume, float isolevel);

	PolygonBuilder(const Math::CircularCurve3d<float>& curve);

	PolygonBuilder(const Math::Curve3d<float>& curve);

	PolygonBuilder(const Math::TriangleCurve3d<float>& curve);

	PolygonBuilder(const ParticleObject& particle, const float isolevel, const int levelOfDetail, const Math::Space3d<float>& space);

	void create(const std::vector< Math::Triangle3d<float> >& triangles);

	PolygonMesh* build(int id = -1);

	void createFace(Vertex* v1, Vertex* v2, Vertex* v3);

public:
	std::vector<Vertex*> vertices;
	std::vector<Face*> faces;
	std::vector<Edge*> edges;

	void createFaces(const std::vector<Vertex*>& vertices);
};

	}
}

#endif