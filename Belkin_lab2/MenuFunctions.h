#pragma once
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include "Pipe.h"
#include "CS.h"
#include "Validation.h"
#include "Utils.h"
#include "Graph.h"

void AddPipe(std::map<int, Pipe>& pipe_list, int forced_diameter);
void EditPipe(std::map<int, Pipe>& pipe_list, std::vector<int>& found_id);
void AddCS(std::map<int, CS>& cs_list, std::string forced_type);
void EditCS(std::map<int, CS>& cs_list, std::vector<int>& found_id);
template <typename T>
void PacketEdit(std::map<int, T>& container, std::vector<int>& found_id, std::string name, std::unordered_map<int, Node*>& graph);
void PipeMenu(std::map<int, Pipe>& pipe_list, std::unordered_map<int, Node*>& graph);
void CSMenu(std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph);
void ViewAllObjects(const std::map<int, Pipe>& pipe_list, const std::map<int, CS>& cs_list);
void Save(const std::map<int, Pipe>& pipe_list, const std::map<int, CS>& cs_list);
void Upload(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list);
void Menu(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph);

#include "MenuFunctions.inl"