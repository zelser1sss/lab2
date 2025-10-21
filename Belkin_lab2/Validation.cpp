#include "Validation.h"

template <typename T>
T ProverkaNumber()
{
    std::string line;
    while (true) {
        getline(std::cin, line);
        try
        {
            int k = 0;
            for (char w : line) {
                if constexpr (std::is_floating_point_v<T>) {
                    if (w == ',') {
                        k++;
                        if (k > 1) throw std::invalid_argument("Multiple decimals");
                        continue;
                    };
                };
                if (!isdigit(w)) {
                    throw std::invalid_argument("Invalid character");
                };
            };
            T value;
            if constexpr (std::is_integral_v<T>) {
                value = stoi(line);
            }
            else {
                value = stof(line);
            };
            if (value <= 0) {
                throw std::invalid_argument("Number must be positive");
            };
            return value;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "ќшибка!\n¬ведите корректное число: ";
        };
    };
};

template int ProverkaNumber<int>();
template float ProverkaNumber<float>();

bool CheckYesNo() {
    std::string word;
    while (true) {
        getline(std::cin, word);
        if (word == "Yes" || word == "y" || word == "yes") {
            return true;
        }
        else if (word == "No" || word == "n" || word == "no") {
            return false;
        }
        else {
            std::cout << "¬ведите \"Yes\" или \"No\": ";
        };
    };
};