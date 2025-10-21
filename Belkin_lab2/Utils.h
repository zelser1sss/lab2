#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "Pipe.h"
#include "CS.h"

template<typename T>
int GetNextID(const std::map<int, T>& container);

std::vector<int> Packet(const std::vector<int>& found_id);

template<typename T>
void Delete(std::map<int, T>& container, std::vector<int>& found_id, std::vector<int> select_id);

template <typename T>
void DisplayFound(const std::map<int, T>& container, const std::vector<int>& found_id, std::string name);

template <typename T>
std::vector<int> FoundName(std::map<int, T>& container, std::string nameClass);

#include "Utils.inl"
