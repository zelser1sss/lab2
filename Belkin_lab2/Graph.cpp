#include "Graph.h"

Node::Node(int nodeId, CS* compressorStation)
	: id(nodeId), cs(compressorStation) {
};

Edge::Edge(Node* node, Pipe* p, float w)
	: adjacentNode(node), pipe(p), length(w) {
};

float Edge::getLength()
{
	if (pipe->getRepair()) {
		return std::numeric_limits<float>::infinity();
	}
	else {
		return length;
	};
};