#include "IdManager.h"
#include "Pipe.h"
#include "CS.h"
#include <algorithm>

std::map<std::string, int> IdManager::lastIds;

int IdManager::GetNextID(const std::string& type)
{
	if (lastIds.find(type) == lastIds.end()) {
		lastIds[type] = 0;
	};

	lastIds[type]++;
	return lastIds[type];

};

template<typename T>
void IdManager::Update(const std::map<int, T>& container, const std::string& type)
{
	if (!container.empty()) {
		int maxId = std::max_element(container.begin(), container.end(), [](const auto& a, const auto& b) {return a.first < b.first; })->first;

		if (maxId > lastIds[type]) {
			lastIds[type] = maxId;
		};
	};
};

template void IdManager::Update<Pipe>(const std::map<int, Pipe>&, const std::string&);
template void IdManager::Update<CS>(const std::map<int, CS>&, const std::string&);
