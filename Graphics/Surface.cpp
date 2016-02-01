#include "Surface.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;


template<typename T>
void Surface<T>::add(const Triangle<T>& t)
{
	const auto normal = t.getNormal();
	std::vector< Vertex<T> > vs;
	vs.push_back(Vertex<T>(t.getv0(), normal, Math::Vector3d<float>(0, 0, 0) ));
	vs.push_back(Vertex<T>(t.getv1(), normal, Math::Vector3d<float>(0, 0, 0) ));
	vs.push_back(Vertex<T>(t.getv2(), normal, Math::Vector3d<float>(0, 0, 0) ));

	const auto& es = HalfEdge<T>::createClosed(vs);
	edges.insert(edges.end(), es.begin(), es.end());

	vertices.insert(vertices.end(), vs.begin(), vs.end());
	auto f = Face<T>(es);
	faces.push_back(f);
}

template<typename T>
void Surface<T>::add(const Box<T>& box)
{
	const auto minx = box.getMinX();
	const auto miny = box.getMinY();
	const auto minz = box.getMinZ();
	const auto maxx = box.getMaxX();
	const auto maxy = box.getMaxY();
	const auto maxz = box.getMaxZ();

	std::vector< Vertex<T> > vs;
	vs.push_back(Vertex<T>(Math::Vector3d<T>(minx, miny, minz)));
	vs.push_back(Vertex<T>(Math::Vector3d<T>(maxx, miny, minz)));
	vs.push_back(Vertex<T>(Math::Vector3d<T>(maxx, maxy, minz)));
	vs.push_back(Vertex<T>(Math::Vector3d<T>(minx, maxy, minz)));
	vs.push_back(Vertex<T>(Math::Vector3d<T>(minx, miny, maxz)));
	vs.push_back(Vertex<T>(Math::Vector3d<T>(maxx, miny, maxz)));
	vs.push_back(Vertex<T>(Math::Vector3d<T>(maxx, maxy, maxz)));
	vs.push_back(Vertex<T>(Math::Vector3d<T>(minx, maxy, maxz)));

	vertices.insert(vertices.end(), vs.begin(), vs.end());

	const auto& es1 = HalfEdge<T>::createClosed({ vs[0], vs[1], vs[2], vs[3] });
	const auto& es2 = HalfEdge<T>::createClosed({ vs[4], vs[5], vs[6], vs[7] });
	edges.insert(edges.end(), es1.begin(), es1.end());
	edges.insert(edges.end(), es2.begin(), es2.end());
	edges.push_back(HalfEdge<T>(vs[0], vs[4]));
	edges.push_back(HalfEdge<T>(vs[1], vs[5]));
	edges.push_back(HalfEdge<T>(vs[2], vs[6]));
	edges.push_back(HalfEdge<T>(vs[3], vs[7]));
}

template class Surface<float>;