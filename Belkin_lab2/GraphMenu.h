#pragma once
#include <map>
#include "Pipe.h"
#include "CS.h"
#include "Graph.h"

void GraphMenu(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::map<int, Node*>& graph);
