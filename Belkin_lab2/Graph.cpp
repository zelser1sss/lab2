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

int Edge::getCapacity()
{
	if (pipe->getRepair()) {
		return 0;
	}
	else {
		std::map<int, int> pipePerfomance = { {530, 5}, {720, 15}, {1020, 30}, {1220, 60}, {1420, 90} };
		return pipePerfomance[pipe->getDiameter()];
	};

};