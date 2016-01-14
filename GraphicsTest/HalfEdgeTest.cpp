#include "gtest/gtest.h"

#include "../Graphics/HalfEdge.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;


/*
TEST(HalfEdgeTest, TestCreateOpen)
{
	using T = float;
	const auto& vs = Vertex<T>::create({ Vector3d<T>(0, 0, 0), Vector3d<T>(1, 0, 0) } );
	const auto& edges = HalfEdge<T>::createOpen(vs);
	EXPECT_EQ(1, edges.size());
	EXPECT_EQ(nullptr, edges.front().getNext());
}
*/

TEST(HalfEdgeTest, TestCreateClosed)
{
	using T = float;
	const auto& vs = Vertex<T>::create({ Vector3d<T>(0, 0, 0), Vector3d<T>(1, 0, 0) });
	const auto& edges = HalfEdge<T>::createClosed(vs);
	EXPECT_EQ(2, edges.size());
}