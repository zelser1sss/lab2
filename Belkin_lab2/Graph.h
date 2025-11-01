	#pragma once
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
	public:
		Node* adjacentNode;
		Pipe* pipe;
		float weight;

		Edge(Node* node, Pipe* p, float w)
			: adjacentNode(node), pipe(p), weight(w) {}
	};

