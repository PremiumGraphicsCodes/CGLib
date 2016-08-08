#include "stdafx.h"
#include "IndexedPolygonSource.h"
#include "PolygonMesh.h"
#include "VertexCollection.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

IndexedPolygonSource::IndexedPolygonSource(
	const std::vector<Vector3d<float>>& positions,
	const std::vector<Vector3d<float>>& normals,
	const std::vector<Vector2d<float>>& texCoords) :
	positions(positions),
	normals(normals),
	texCoords(texCoords)
{
}

#include "PolygonBuilder.h"

void IndexedPolygonSource::build(const std::vector<IndexedFace>& faces)
{
	std::vector<Vertex*> vertices;
	int currentIndex = 0;
	std::vector<std::vector<Vertex*>> faceVertex;

	for (const auto& face : faces) {
		std::vector<Vertex*> vs;
		for (const auto& v : face.vertices) {
			Vector3d<float> pos = positions[v.positionIndex];
			Vector3d<float> normal;
			if (v.normalIndex != -1) {
				normal = normals[v.normalIndex];
			}
			Vector2d<float> texCoord;
			if (v.texCoordIndex != -1) {
				texCoord = texCoords[v.texCoordIndex];
			}
			vertices.push_back(new Vertex(pos, normal, texCoord));
			vs.push_back(vertices.back());
		}
		faceVertex.push_back(vs);

	}
	PolygonBuilder builder(vertices);
	for (auto fv : faceVertex) {
		builder.createFaces(fv);
	}
	this->polygon = builder.build();
}
