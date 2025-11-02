#include "Pipe.h"
#include "Validation.h"

Pipe::Pipe(int id,  const std::string& name, float length, int diameter, bool repair)
    : id(id), name(name), length(length), diameter(diameter), repair(repair) {
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
        std::cout << "Введите диаметр трубы (мм): ";
        pipe.diameter = ProverkaNumber<int>();
    }
    else {
        std::cout << "Диаметр трубы: " << pipe.diameter << " мм (установлен автоматически)\n";
    };
    

    std::cout << "Труба на ремонте?(Yes/No): ";
    pipe.repair = CheckYesNo();

    return in;
};