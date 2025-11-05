#pragma once
#include <map>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <unordered_set>
#include "Pipe.h"
#include "CS.h"
#include "Graph.h"
#include "Logger.h"

bool isPipeUsed(const std::unordered_map<int, Node*>& graph, int pipe_id);
bool isCSUsed(const std::unordered_map<int, Node*>& graph, int cs_id);
Node* addOrGetNode(std::unordered_map<int, Node*>& graph, int value, std::map<int, CS>& cs_list);
void CreateGraph(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph, std::vector<int>& selected_data);
int FoundDiameter(std::map<int, Pipe>& pipe_list, std::unordered_map<int, Node*>& graph);
void FoundType(std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph, int& cs_start, int& cs_end);
void RemoveEdge(std::unordered_map<int, Node*>& graph, std::vector<int>& pipe_id);
void RemoveNode(std::unordered_map<int, Node*>& graph, std::vector<int>& cs_ids);
bool hasCycleDFS(Node* node, std::unordered_set<Node*>& visited, std::unordered_set<Node*>& recursionStack);
bool isAcyclicGraph(std::unordered_map<int, Node*>& graph);
std::vector<int> topologicalSort(std::unordered_map<int, Node*>& graph);
void initHashTables(Node* start, std::unordered_map<int, Node*>& graph, std::unordered_set<Node*>& unprocessedNodes, std::unordered_map<Node*, float>& lengthToNodes);
Node* getNodeWithMinLengthTolt(std::unordered_set<Node*>& unprocessedNodes, std::unordered_map<Node*, float>& lengthToNodes);
void calculateLengthToEachNode(std::unordered_set<Node*>& unprocessedNodes, std::unordered_map<Node*, float>& lengthToNodes);
std::vector<Node*> getShortestPath(Node* start, Node* end, std::unordered_map<Node*, float>& lengthToNodes);
std::vector<Node*> getShortestPath(std::unordered_map<int, Node*>& graph, Node* start, Node* end);
void FunctionToCreateGraph(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph);
void FunctionToRemoveEdge(std::unordered_map<int, Node*>& graph);
void FunctionToRemoveNode(std::unordered_map<int, Node*>& graph);
void FunctionToTopologicalSort(std::unordered_map<int, Node*>& graph);
void DisplayGraph(const std::unordered_map<int, Node*>& graph);
void FunctionToFindShortPath(std::unordered_map<int, Node*>& graph);
void GraphMenu(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph);
