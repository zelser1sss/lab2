#include "Utils.h"
#include <iostream>
#include <sstream>
#include <algorithm>

std::vector<int> Packet(const std::vector<int>& found_id)
{
    std::vector<int> select_id;
    std::string line;
    getline(std::cin, line);
    std::stringstream ss(line);
    std::string word;

    while (ss >> word) {
        try {
            int id = stoi(word);
            bool found = false;

            for (int i : found_id) {
                if (i == id) {
                    select_id.push_back(id);
                    found = true;
                    break;
                };
            };

            if (!found) {
                std::cout << "ID:" << word << " нету среди найденных" << std::endl;
            };
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Ошибка: '" << word << "' не является числом!" << std::endl;
        };
    };

    return select_id;
};