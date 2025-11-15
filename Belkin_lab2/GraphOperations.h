#pragma once
#include "Graph.h"
#include "Pipe.h"
#include "CS.h"
#include <map>
#include <unordered_map>
#include <vector>
#include "Validation.h"
#include "Utils.h"
#include <iostream>


bool isUsedInGraph(const std::unordered_map<int, Node*>& graph, int id, std::string name_class);
Node* addOrGetNode(std::unordered_map<int, Node*>& graph, int value, std::map<int, CS>& cs_list);
void CreateGraph(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph, std::vector<int>& selected_data);


int FoundDiameter(std::map<int, Pipe>& pipe_list, std::unordered_map<int, Node*>& graph);
void FoundType(std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph, int& cs_start, int& cs_end);
template <typename T>
int FoundObject(std::map<int, T>& container, std::unordered_map<int, Node*>& graph, int input, std::string name);


void RemoveEdge(std::unordered_map<int, Node*>& graph, std::vector<int>& pipe_id);
void RemoveNode(std::unordered_map<int, Node*>& graph, std::vector<int>& cs_ids);


template <typename T>
int isReal(std::map<int, T>& container, std::string name);


#include "GraphOperations.inl"