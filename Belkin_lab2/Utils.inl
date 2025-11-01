#ifndef UTILS_INL
#define UTILS_INL

#include "IdManager.h"

template<typename T>
int GetNextID(const std::map<int, T>& container)
{
    if constexpr (std::is_same_v<T, Pipe>) {
        IdManager::Update(container, "pipe");
        return IdManager::GetNextID("pipe");
    }
    else if constexpr (std::is_same_v<T, CS>) {
        IdManager::Update(container, "cs");
        return IdManager::GetNextID("cs");
    };
    return 1;
};

template<typename T>
void Delete(std::map<int, T>& container, std::vector<int>& found_id, std::vector<int> select_id)
{
    for (int i : select_id) {
        container.erase(i);
    };

    for (int i : found_id) {
        for (int j : select_id) {
            if (i == j) {
                found_id.erase(std::remove(found_id.begin(), found_id.end(), i), found_id.end());
            };
        };
    };
};

template <typename T>
void DisplayFound(const std::map<int, T>& container, const std::vector<int>& found_id, std::string name)
{
    std::cout << "\nНайденные " << name << ":\n--------------------------------------\n";
    if constexpr (std::is_same_v<T, Pipe>) {
        for (int i : found_id) {
            const Pipe& pipe = container.find(i)->second;
            std::cout << pipe.getName() << " [ID:" << pipe.getId() << "] Диаметр(мм): " << pipe.getDiameter() << " | Статус в ремонте : ";
            if (pipe.getRepair() == true) {
                std::cout << "ДА" << std::endl;
            }
            else {
                std::cout << "НЕТ" << std::endl;
            };
        };
    }
    else if constexpr (std::is_same_v<T, CS>) {
        for (int i : found_id) {
            const CS& cs = container.find(i)->second;
            std::cout << cs.getName() << " [ID:" << cs.getId() << "]\nПроцент незадействованных цехов в работе: " << cs.getUnusedPercent() << "% (" << cs.getKCexInWork() << "/" << cs.getKCex() << ")" << std::endl;
        };
    };
    std::cout << "--------------------------------------\n\n";
};

template <typename T>
std::vector<int> FoundName(std::map<int, T>& container, std::string nameClass)
{
    std::vector<int> found_id;
    if (container.empty())
    {
        std::cout << "\nЭлементов нет\n\n";
        return found_id;
    };

    std::cout << "\nВведите название " << nameClass << ": ";
    std::string name;
    getline(std::cin, name);

    for (const auto& element : container) {
        if (element.second.getName().find(name) != std::string::npos) {
            found_id.push_back(element.first);
        };
    };
    if (found_id.empty()) {
        std::cout << "\n" << nameClass << " не найдены!\n\n";
        return found_id;
    };
    return found_id;
};

#endif