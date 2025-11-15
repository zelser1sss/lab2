
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

void FunctionToRemoveEdge(std::unordered_map<int, Node*>& graph, std::map<int, Pipe>& pipe_list);
void FunctionToRemoveNode(std::unordered_map<int, Node*>& graph, std::map<int, CS>& cs_list);
void FunctionToTopologicalSort(std::unordered_map<int, Node*>& graph);
void DisplayGraph(const std::unordered_map<int, Node*>& graph);
void FunctionToFindShortPath(std::unordered_map<int, Node*>& graph, std::map<int, CS>& cs_list);
void FunctionToFindMaxFlow(std::unordered_map<int, Node*>& graph, std::map<int, CS>& cs_list);
void GraphMenu(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph);
