#include "CS.h"
#include "Validation.h"

CS::CS(int id, const std::string& name, int k_cex, int k_cex_in_work, const std::string& type)
    : id(id), name(name), k_cex(k_cex), k_cex_in_work(k_cex_in_work), type(type) {
};

float CS::getUnusedPercent() const {
    if (k_cex == 0) return 0.0f;
    return (static_cast<float>(k_cex - k_cex_in_work) / k_cex) * 100;
};

bool CS::startWorkshops(int count) {
    if (k_cex_in_work + count <= k_cex) {
        k_cex_in_work += count;
        return true;
    };
    return false;
};

bool CS::stopWorkshops(int count) {
    if (k_cex_in_work - count >= 0) {
        k_cex_in_work -= count;
        return true;
    };
    return false;
};

std::ostream& operator<<(std::ostream& out, const CS& cs) {
    out << "�� [ID:" << cs.id << "]" << std::endl;
    out << "��������: " << cs.name << std::endl;
    out << "����� ���������� �����: " << cs.k_cex << std::endl;
    out << "���������� ����� � ������: " << cs.k_cex_in_work << std::endl;
    out << "���: " << cs.type << std::endl;
    out << "������� ����������������� �����: " << cs.getUnusedPercent() << "%" << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, CS& cs) {

    std::cout << "\n������� �������� ��: ";
    getline(std::cin, cs.name);

    std::cout << "������� ����� ���������� �����: ";
    cs.k_cex = ProverkaNumber<int>();

    std::cout << "������� ���������� ����� � ������: ";
    cs.k_cex_in_work = ProverkaNumber<int>();
    if (cs.k_cex_in_work > cs.k_cex) {
        std::cout << "������! ���������� ����� � ������ �� ����� ���� ������ ������ ���������� �����\n������� ���������� �����: ";
        cs.k_cex_in_work = ProverkaNumber<int>();
    };

    std::cout << "������� ��� ��: ";
    getline(std::cin, cs.type);

    return in;
};