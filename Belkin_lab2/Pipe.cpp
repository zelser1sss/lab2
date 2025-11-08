#include "Pipe.h"
#include "Validation.h"

Pipe::Pipe(int id,  const std::string& name, float length, int diameter, bool repair)
    : id(id), name(name), length(length), diameter(diameter), repair(repair) {
};

const std::vector<int> Pipe::allowed_diameters = { 530, 720, 1020, 1220, 1420, 0 };

bool Pipe::setDiameter(int newDiameter) {
    if (isValidDiameter(newDiameter)) {
        diameter = newDiameter;
        return true;
    };
    return false;
};

bool Pipe::isValidDiameter(int diameter) {
    return std::find(allowed_diameters.begin(), allowed_diameters.end(), diameter)
        != allowed_diameters.end();
};

const std::vector<int>& Pipe::getAllowedDiameters() {
    return allowed_diameters;
};

std::ostream& operator<<(std::ostream& out, const Pipe& pipe) {
    out << "Труба [ID:" << pipe.id << "]" << std::endl;
    out << "Название: " << pipe.name << std::endl;
    out << "Длина: " << pipe.length << std::endl;
    out << "Диаметр: " << pipe.diameter << std::endl;
    out << "В ремонте: " << (pipe.repair ? "Да" : "Нет") << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Pipe& pipe) {

    std::cout << "\nВведите название трубы: ";
    getline(in, pipe.name);

    std::cout << "Введите длину трубы (км): ";
    pipe.length = ProverkaNumber<float>();

    if (pipe.diameter == 0) {
        bool validDiameter = false;
        while (!validDiameter) {
            std::cout << "Введите диаметр трубы (мм)";
            std::cout << " [допустимые: ";
            const auto& allowed = Pipe::getAllowedDiameters();
            for (size_t i = 0; i < allowed.size()-1; ++i) {
                std::cout << allowed[i];
                if (i < allowed.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "]: ";

            int tempDiameter = ProverkaNumber<int>();

            if (Pipe::isValidDiameter(tempDiameter)) {
                pipe.diameter = tempDiameter;
                validDiameter = true;
            }
            else {
                std::cout << "Ошибка: Неверный диаметр! Пожалуйста, используйте одно из допустимых значений." << std::endl;
            }
        }
    }
    else {
        std::cout << "Диаметр трубы : " << pipe.diameter << " мм(установлен автоматически)\n";
    };
    

    std::cout << "Труба на ремонте?(Yes/No): ";
    pipe.repair = CheckYesNo();

    return in;
};