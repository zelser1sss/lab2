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
private:
	int id;
	CS* cs;
	std::vector<Edge*> edges;
	std::map<Node*, Edge*> parents;

public:

	Node(int nodeId, CS* compressorStation);

	int getId() const { return id; };
	CS* getCS() const { return cs; };
	std::vector<Edge*>& getEdges() { return edges; }
	std::map<Node*, Edge*>& getParents() { return parents; }
};

class Edge
{
private:
	float length;
	Pipe* pipe;
	Node* adjacentNode;

public:

	Edge(Node* node, Pipe* p, float w);

	Pipe* getPipe() const { return pipe; };
	Node* getAdjacentNode() const { return adjacentNode; };
	float getLength();
	float getWeight() const { return length; };
};

