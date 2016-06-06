#include "Edge.h"

using namespace Crystal::Core;

Edge::Edge(Node* start, Node* end, const int id) :
	start(start),
	end(end),
	id(id)
{
}