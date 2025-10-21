#include "Pipe.h"
#include "Validation.h"

Pipe::Pipe(int id,  const std::string& name, float length, int diameter, bool repair)
    : id(id), name(name), length(length), diameter(diameter), repair(repair) {
};

std::ostream& operator<<(std::ostream& out, const Pipe& pipe) {
    out << "����� [ID:" << pipe.id << "]" << std::endl;
    out << "��������: " << pipe.name << std::endl;
    out << "�����: " << pipe.length << std::endl;
    out << "�������: " << pipe.diameter << std::endl;
    out << "� �������: " << (pipe.repair ? "��" : "���") << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Pipe& pipe) {

    std::cout << "\n������� �������� �����: ";
    getline(in, pipe.name);

    std::cout << "������� ����� ����� (��): ";
    pipe.length = ProverkaNumber<float>();

    std::cout << "������� ������� ����� (��): ";
    pipe.diameter = ProverkaNumber<int>();

    std::cout << "����� �� �������?(Yes/No): ";
    pipe.repair = CheckYesNo();

    return in;
};