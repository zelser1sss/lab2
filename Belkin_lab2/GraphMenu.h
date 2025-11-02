#pragma once
#include <map>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include "Pipe.h"
#include "CS.h"
#include "Graph.h"

bool isPipeUsed(const std::unordered_map<int, Node*>& graph, int pipe_id);
bool isCSUsed(const std::unordered_map<int, Node*>& graph, int cs_id);
Node* addOrGetNode(std::unordered_map<int, Node*>& graph, int value, std::map<int, CS>& cs_list);
void CreateGraph(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph, std::vector<int>& selected_data);
int FoundDiameter(std::map<int, Pipe>& pipe_list, std::unordered_map<int, Node*>& graph);
void FoundType(std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph, int& cs_start, int& cs_end);
void RemoveEdge(std::unordered_map<int, Node*>& graph, std::vector<int>& pipe_id);
void RemoveNode(std::unordered_map<int, Node*>& graph, std::vector<int>& cs_ids);
void FunctionToCreateGraph(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph);
void FunctionToRemoveEdge(std::unordered_map<int, Node*>& graph);
void FunctionToRemoveNode(std::unordered_map<int, Node*>& graph);
void GraphMenu(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph);
