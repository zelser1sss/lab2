#include "MenuFunctions.h"
#include <iostream>
#include <fstream>
#include <sstream>

void AddPipe(std::map<int, Pipe>& pipe_list)
{
    Pipe newPipe;
    std::cin >> newPipe;

    int newId = GetNextID(pipe_list);
    newPipe.setId(newId);
    pipe_list[newId] = newPipe;

    std::cout << "\nНовая труба добавлена\n\n";
};

void EditPipe(std::map<int, Pipe>& pipe_list, std::vector<int>& found_id)
{
    if (found_id.empty()) {
        std::cout << "\nТруб нет!\n";
        return;
    };

    std::string status;
    std::cout << "\nТруба/ы в ремонте?(Yes/No): ";
    while (true) {
        getline(std::cin, status);
        if (status == "Yes" || status == "y" || status == "yes") {
            for (int i : found_id) {
                pipe_list[i].setRepair(true);
            };
            std::cout << "\nСтатус \"в ремонте\" сменен на \"Да\"\n";
            break;
        }
        else if (status == "No" || status == "n" || status == "no") {
            for (int i : found_id) {
                pipe_list[i].setRepair(false);
            };
            std::cout << "\nСтатус \"в ремонте\" сменен на \"Нет\"\n";
            break;
        }
        else {
            std::cout << "Ошибка! Введите \"Yes\" или \"No\": ";
        };
    };
};

void AddCS(std::map<int, CS>& cs_list)
{
    CS newCS;
    std::cin >> newCS;

    int newId = GetNextID(cs_list);
    newCS.setId(newId);
    cs_list[newId] = newCS;

    std::cout << "\nНовая КС добавлена\n\n";
};

void EditCS(std::map<int, CS>& cs_list, std::vector<int>& found_id)
{
    if (found_id.empty()) {
        std::cout << "\nКС нет!\n";
        return;
    };

    while (1)
    {
        DisplayFound(cs_list, found_id, "КС");
        std::cout << "--------------------------------------\n";
        std::cout << "Выберите опцию:\n1. Запустить цеха\n2. Остановить цеха\n3. Вернутся обратно\n";
        std::cout << "--------------------------------------\n\n";
        int option = ProverkaNumber<int>();

        switch (option)
        {
        case 1:
        {
            std::cout << "\nВведите сколько цехов запустить: ";
            int count = ProverkaNumber<int>();
            for (auto& element : found_id) {
                if (!cs_list[element].startWorkshops(count)) {
                    std::cout << "\nНельзя запустить больше цехов чем доступно!\n";
                    break;
                };
            };
            break;
        };
        case 2:
        {
            std::cout << "\nВведите сколько цехов остановить: ";
            int count = ProverkaNumber<int>();
            for (auto& element : found_id) {
                if (!cs_list[element].stopWorkshops(count)) {
                    std::cout << "\nНельзя остановить больше цехов чем работает!\n";
                    break;
                };
            };
            break;
        };
        case 3:
            return;
        };
    };
};

void PipeMenu(std::map<int, Pipe>& pipe_list)
{
    while (1) {
        std::cout << "--------------------------------------\n";
        std::cout << "Выберите опцию:\n1. Добавить трубу\n2. Найти по названию\n3. Найти по признаку \"в ремонте\"\n4. Выйти в главное меню\n";
        std::cout << "--------------------------------------\n\n";
        int option = ProverkaNumber<int>();
        std::vector<int> found_id;

        switch (option)
        {
        case 1:
            AddPipe(pipe_list);
            break;
        case 2: {
            found_id = FoundName(pipe_list, "трубы");
            if (!found_id.empty()) {
                PacketEdit(pipe_list, found_id, "трубы");
            };
            break;
        };
        case 3:
        {
            if (pipe_list.empty())
            {
                std::cout << "\nТруб нет\n\n";
                break;
            };

            found_id.clear();
            std::cout << "\nИскать трубы в ремонте(Yes/No): ";
            bool status = CheckYesNo();

            for (const auto& element : pipe_list) {
                if (element.second.getRepair() == status) {
                    found_id.push_back(element.first);
                };
            };
            if (found_id.empty()) {
                std::cout << "\nТрубы не найдены!\n\n";
                break;
            };
            PacketEdit(pipe_list, found_id, "трубы");
            break;
        };
        case 4:
            std::cout << "\nВозвращаемся в главное меню...\n\n";
            return;
        default:
            std::cout << "Неизвестная опция. Попробуйте еще раз\n\n";
            break;
        };
    };
};

void CSMenu(std::map<int, CS>& cs_list)
{
    while (1) {
        std::cout << "--------------------------------------\n";
        std::cout << "Выберите опцию:\n1. Добавить КС\n2. Найти по названию\n3. Найти по признаку проценту незадействованных\n4. Выйти в главное меню\n";
        std::cout << "--------------------------------------\n\n";
        int option = ProverkaNumber<int>();
        std::vector<int> found_id;

        switch (option)
        {
        case 1:
            AddCS(cs_list);
            break;
        case 2:
        {
            found_id = FoundName(cs_list, "КС");
            if (!found_id.empty()) {
                PacketEdit(cs_list, found_id, "КС");
            };
            break;
        };
        case 3:
        {
            if (cs_list.empty())
            {
                std::cout << "\nКС нет\n\n";
                break;
            };

            found_id.clear();
            std::cout << "\nВведите процент незадействованных цехов: ";
            int percent = ProverkaNumber<int>();

            for (const auto& element : cs_list) {
                if (element.second.getUnusedPercent() == percent) {
                    found_id.push_back(element.first);
                };
            };
            if (found_id.empty()) {
                std::cout << "\nКС не найдены!\n\n";
                break;
            };
            PacketEdit(cs_list, found_id, "КС");
            break;
        };
        case 4:
            std::cout << "\nВозвращаемся в главное меню...\n\n";
            return;
        default:
            std::cout << "Неизвестная опция. Попробуйте еще раз\n\n";
            break;
        };
    };
};

void ViewAllObjects(const std::map<int, Pipe>& pipe_list, const std::map<int, CS>& cs_list)
{
    if (pipe_list.empty()) {
        std::cout << "\nТРУБ НЕТ\n";
    }
    else {
        std::cout << "\nВСЕ ТРУБЫ:\n--------------------------------------\n";
        for (const auto& element : pipe_list) {
            std::cout << element.second << "--------------------------------------\n";
        };
    };

    if (cs_list.empty()) {
        std::cout << "КС НЕТ\n\n";
    }
    else {
        std::cout << "\nВСЕ КС:\n--------------------------------------\n";
        for (const auto& element : cs_list) {
            std::cout << element.second << "--------------------------------------\n";
        };
        std::cout << std::endl;
    };
};

void Save(const std::map<int, Pipe>& pipe_list, const std::map<int, CS>& cs_list)
{
    std::string file;
    std::cout << "\nВведите название файла: ";
    getline(std::cin, file);

    std::ofstream save;
    save.open(file);
    if (save.is_open()) {
        if (!(pipe_list.empty())) {
            save << "ТРУБЫ\n";
            for (const auto& element : pipe_list) {
                save << element.second.getId() << "|" << element.second.getName() << "|" << element.second.getLength() << "|" << element.second.getDiameter() << "|" << element.second.getRepair() << "|" << std::endl;
            };
            std::cout << "\nСписок труб сохранен!\n";
        }
        else {
            save << "ТРУБ НЕТ\n";
            std::cout << "\nТРУБ НЕТ\n";
        };

        if (!(cs_list.empty())) {
            save << "КС\n";
            for (const auto& element : cs_list) {
                save << element.second.getId() << "|" << element.second.getName() << "|" << element.second.getKCex() << "|" << element.second.getKCexInWork() << "|" << element.second.getType() << "|" << std::endl;
            };
            std::cout << "Список КС сохранен!\n\n";
        }
        else {
            save << "КС НЕТ";
            std::cout << "КС НЕТ\n\n";
        };
    }
    else {
        std::cout << "\nНедопустимое имя файла!\n\n";
        return;
    };
};

void Upload(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list)
{
    std::string file;
    std::cout << "\nВведите имя файла: ";
    getline(std::cin, file);

    std::string line;
    std::string state = "None";
    std::ifstream upload(file);

    if (!(upload.is_open())) {
        std::cout << "\nФайл '" << file << "' не найден\n\n";
        return;
    };

    pipe_list.clear();
    cs_list.clear();

    while (getline(upload, line)) {
        if (line.empty() || line.find_first_not_of(' ') == std::string::npos) {
            continue;
        };

        if ("ТРУБ НЕТ" == line) {
            std::cout << "\nТРУБ НЕТ\n";
            continue;
        }
        else if ("ТРУБЫ" == line) {
            state = "Trubs";
            continue;
        };

        if ("КС НЕТ" == line) {
            std::cout << "КС НЕТ\n";
            continue;
        }
        else if ("КС" == line) {
            state = "CS";
            continue;
        };

        std::vector<size_t> pos = { 0 };
        for (size_t i = 0; i < 5; i++) {
            size_t found_pos = line.find('|', pos[i]);
            pos.push_back(found_pos + 1);
        };

        std::vector<std::string> sub;
        for (size_t i = 0; i < (pos.size() - 1); i++) {
            std::string found_sub = line.substr(pos[i], pos[i + 1] - pos[i] - 1);
            sub.push_back(found_sub);
        };

        if (state == "Trubs") {
            int ID = stoi(sub[0]);
            Pipe newPipe(ID, sub[1], stof(sub[2]), stoi(sub[3]), stoi(sub[4]));
            pipe_list.emplace(ID, newPipe);
        };

        if (state == "CS") {
            int ID = stoi(sub[0]);
            CS newCS(ID, sub[1], stoi(sub[2]), stoi(sub[3]), sub[4]);
            cs_list.emplace(ID, newCS);
        };
    };
    std::cout << std::endl;
    upload.close();
};

void Menu(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list)
{
    while (1) {
        std::cout << "--------------------------------------\n";
        std::cout << "Выберите опцию:\n1. Меню труб\n2. Меню КС\n3. Просмотр всех объектов\n4. Сохранить\n5. Загрузить\n9. Выход\n";
        std::cout << "--------------------------------------\n\n";
        int option;
        option = ProverkaNumber<int>();

        switch (option)
        {
        case 1:
            std::cout << std::endl;
            PipeMenu(pipe_list);
            break;
        case 2:
            std::cout << std::endl;
            CSMenu(cs_list);
            break;
        case 3:
            ViewAllObjects(pipe_list, cs_list);
            break;
        case 4:
            Save(pipe_list, cs_list);
            break;
        case 5:
            Upload(pipe_list, cs_list);
            break;
        case 9:
            std::cout << "\nВыходим...\n";
            return;
        default:
            std::cout << "Неизвестная опция. Попробуйте еще раз\n\n";
            break;
        };
    };
};