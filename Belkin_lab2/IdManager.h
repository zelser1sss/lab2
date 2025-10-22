#pragma once
#include <string>
#include <map>

class IdManager
{
private:

	static std::map<std::string, int> lastIds;

public:

	static int GetNextID(const std::string& type);

	template<typename T>
	static void Update(const std::map<int, T>& container, const std::string& type);

};

