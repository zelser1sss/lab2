#pragma once
#include "Graph.h"
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <list>


bool hasCycleDFS(Node* node, std::unordered_set<Node*>& visited, std::unordered_set<Node*>& recursionStack);
bool isAcyclicGraph(std::unordered_map<int, Node*>& graph);
std::vector<int> topologicalSort(std::unordered_map<int, Node*>& graph);


void initHashTables(Node* start, std::unordered_map<int, Node*>& graph, std::unordered_set<Node*>& unprocessedNodes, std::unordered_map<Node*, float>& lengthToNodes);
Node* getNodeWithMinLengthTolt(std::unordered_set<Node*>& unprocessedNodes, std::unordered_map<Node*, float>& lengthToNodes);
void calculateLengthToEachNode(std::unordered_set<Node*>& unprocessedNodes, std::unordered_map<Node*, float>& lengthToNodes);
std::vector<Node*> getShortestPath(Node* start, Node* end, std::unordered_map<Node*, float>& lengthToNodes);
std::vector<Node*> getShortestPath(std::unordered_map<int, Node*>& graph, Node* start, Node* end);


bool dfs(std::unordered_map<int, Node*>& graph, int src, int dst, std::list<Edge*>& path, std::unordered_set<int>& visited);
int find_min_flow(const std::list<Edge*>& path);
int ford_fulkerson(std::unordered_map<int, Node*>& graph, int src, int dst);
