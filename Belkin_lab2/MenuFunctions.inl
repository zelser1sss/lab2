#ifndef MENUFUNCTIONS_INL
#define MENUFUNCTIONS_INL

template <typename T>
void PacketEdit(std::map<int, T>& container, std::vector<int>& found_id, std::string name)
{
    while (1) {
        DisplayFound(container, found_id, name);
        std::cout << "--------------------------------------\n";
        std::cout << "�������� �����:\n1. ������������� ��� ���������\n2. ������������� ���� ��� ��������� ��������� � ������ ���������\n3. ������� ��� ���������\n4. ������� ���� ��� ��������� ��������� � ������ ���������\n5. �������� �������\n";
        std::cout << "--------------------------------------\n\n";
        int option = ProverkaNumber<int>();

        switch (option)
        {
        case 1:
            if constexpr (std::is_same_v<T, Pipe>) {
                EditPipe(container, found_id);
            };
            if constexpr (std::is_same_v<T, CS>) {
                EditCS(container, found_id);
            };
            break;
        case 2:
        {
            std::cout << "\n������� ID ��������(-��) ����� ������ : ";
            std::vector<int> select_id = Packet(found_id);
            if constexpr (std::is_same_v<T, Pipe>) {
                EditPipe(container, select_id);
            };
            if constexpr (std::is_same_v<T, CS>) {
                EditCS(container, select_id);
            };
            break;
        };
        case 3:
            if (found_id.empty()) {
                std::cout << "\n��������� ���!\n";
                break;
            };
            Delete(container, found_id, found_id);
            std::cout << "\n�������� �������!\n\n";
            return;
        case 4:
        {
            std::cout << "\n������� ID ��������(-��) ����� ������: ";
            std::vector<int> select_id = Packet(found_id);

            if (select_id.empty()) {
                std::cout << "\n��������� ���!\n";
                break;
            };
            Delete(container, found_id, select_id);
            std::cout << "\n�������� �������!\n";
            break;
        };
        case 5:
            std::cout << std::endl;
            return;
        default:
            std::cout << "����������� �����. ���������� ��� ���\n\n";
        };
    };
};

#endif