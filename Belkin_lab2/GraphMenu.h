#pragma once
#include <map>
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"
#include "Graph.h"

void GraphMenu(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph);
