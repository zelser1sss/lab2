#ifndef MENUFUNCTIONS_INL
#define MENUFUNCTIONS_INL

template <typename T>
void PacketEdit(std::map<int, T>& container, std::vector<int>& found_id, std::string name, std::unordered_map<int, Node*>& graph)
{
    while (1) {
        DisplayFound(container, found_id, name);
        std::cout << "--------------------------------------\n";
        std::cout << "Выберите опцию:\n1. Редактировать все найденные\n2. Редактировать один или несколько элементов в списке найденных\n3. Удалить все найденные\n4. Удалить один или несколько элементов в списке найденных\n5. Вернутся обратно\n";
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
            std::cout << "\nВведите ID элемента(-ов) через пробел : ";
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
                std::cout << "\nЭлементов нет!\n";
                break;
            };
            Delete(container, found_id, found_id, graph);
            std::cout << "\nЭлементы удалены!\n\n";
            return;
        case 4:
        {
            std::cout << "\nВведите ID элемента(-ов) через пробел: ";
            std::vector<int> select_id = Packet(found_id);

            if (select_id.empty()) {
                std::cout << "\nЭлементов нет!\n";
                break;
            };
            Delete(container, found_id, select_id, graph);
            std::cout << "\nЭлементы удалены!\n";
            break;
        };
        case 5:
            std::cout << std::endl;
            return;
        default:
            std::cout << "Неизвестная опция. Попробуйте еще раз\n\n";
        };
    };
};

#endif