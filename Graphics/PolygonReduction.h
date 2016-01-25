#ifndef __CRYSTAL_GRAPHICS_POLYGON_REDUCTION_H__
#define __CRYSTAL_GRAPHICS_POLYGON_REDUCTION_H__

#include "../Math/Vector3d.h"
#include <list>
#include <array>

namespace Crystal {
	namespace Graphics {
		namespace Experiment {

			class TriangleFace;

			class Vertex
			{
			public:
				Math::Vector3d<float> getPosition() const { return position; }
				
				std::list< TriangleFace* > getFaces() const { return faces; }

			private:
				std::list<TriangleFace*> faces;

				Math::Vector3d<float> position;
			};

			class Edge
			{
			public:
				Edge(Vertex* v1, Vertex* v2) : v1(v1), v2(v2), cost(100000)
				{}

				float computeCost();

				float getLength() const;


			private:
				Vertex* v1;
				Vertex* v2;
				float cost;
			};

			class TriangleFace
			{
			public:
				bool hasVertex(const Vertex* v);

			private:
				
				std::array<Vertex*, 3> vertices;
			};

			class TriangleMesh
			{
			public:
				void reduceTo(const int desired);
			private:
				Edge* getMinimunCostEdge();

				std::list<Vertex*> vertices;
				std::list<Edge*> edges;
				std::list<TriangleFace*> triangles;
			};

		}
	}
}
#endif
