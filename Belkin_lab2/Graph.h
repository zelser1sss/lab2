#pragma once
#include <limits>
#include <vector>
#include <map>
#include "CS.h"
#include "Pipe.h"

class Node;
class Edge;

class Node
{
public:
	int id;
	CS* cs;
	std::vector<Edge*> edges;
	std::map<Node*, Edge*> parents;

	Node(int nodeId, CS* compressorStation)
		: id(nodeId), cs(compressorStation) {
	}
};

class Edge
{
private:
	float length;

public:
	Pipe* pipe;
	Node* adjacentNode;

	Edge(Node* node, Pipe* p, float w)
		: adjacentNode(node), pipe(p), length(w) {
	}
	float getLength()
	{
		if (pipe->getRepair()) {
			return std::numeric_limits<float>::infinity();
		}
		else {
			return length;
		};
	};
};

