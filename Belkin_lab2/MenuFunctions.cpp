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

    std::cout << "\n����� ����� ���������\n\n";
};

void EditPipe(std::map<int, Pipe>& pipe_list, std::vector<int>& found_id)
{
    if (found_id.empty()) {
        std::cout << "\n���� ���!\n";
        return;
    };

    std::string status;
    std::cout << "\n�����/� � �������?(Yes/No): ";
    while (true) {
        getline(std::cin, status);
        if (status == "Yes" || status == "y" || status == "yes") {
            for (int i : found_id) {
                pipe_list[i].setRepair(true);
            };
            std::cout << "\n������ \"� �������\" ������ �� \"��\"\n";
            break;
        }
        else if (status == "No" || status == "n" || status == "no") {
            for (int i : found_id) {
                pipe_list[i].setRepair(false);
            };
            std::cout << "\n������ \"� �������\" ������ �� \"���\"\n";
            break;
        }
        else {
            std::cout << "������! ������� \"Yes\" ��� \"No\": ";
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

    std::cout << "\n����� �� ���������\n\n";
};

void EditCS(std::map<int, CS>& cs_list, std::vector<int>& found_id)
{
    if (found_id.empty()) {
        std::cout << "\n�� ���!\n";
        return;
    };

    while (1)
    {
        DisplayFound(cs_list, found_id, "��");
        std::cout << "--------------------------------------\n";
        std::cout << "�������� �����:\n1. ��������� ����\n2. ���������� ����\n3. �������� �������\n";
        std::cout << "--------------------------------------\n\n";
        int option = ProverkaNumber<int>();

        switch (option)
        {
        case 1:
        {
            std::cout << "\n������� ������� ����� ���������: ";
            int count = ProverkaNumber<int>();
            for (auto& element : found_id) {
                if (!cs_list[element].startWorkshops(count)) {
                    std::cout << "\n������ ��������� ������ ����� ��� ��������!\n";
                    break;
                };
            };
            break;
        };
        case 2:
        {
            std::cout << "\n������� ������� ����� ����������: ";
            int count = ProverkaNumber<int>();
            for (auto& element : found_id) {
                if (!cs_list[element].stopWorkshops(count)) {
                    std::cout << "\n������ ���������� ������ ����� ��� ��������!\n";
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
        std::cout << "�������� �����:\n1. �������� �����\n2. ����� �� ��������\n3. ����� �� �������� \"� �������\"\n4. ����� � ������� ����\n";
        std::cout << "--------------------------------------\n\n";
        int option = ProverkaNumber<int>();
        std::vector<int> found_id;

        switch (option)
        {
        case 1:
            AddPipe(pipe_list);
            break;
        case 2: {
            found_id = FoundName(pipe_list, "�����");
            if (!found_id.empty()) {
                PacketEdit(pipe_list, found_id, "�����");
            };
            break;
        };
        case 3:
        {
            if (pipe_list.empty())
            {
                std::cout << "\n���� ���\n\n";
                break;
            };

            found_id.clear();
            std::cout << "\n������ ����� � �������(Yes/No): ";
            bool status = CheckYesNo();

            for (const auto& element : pipe_list) {
                if (element.second.getRepair() == status) {
                    found_id.push_back(element.first);
                };
            };
            if (found_id.empty()) {
                std::cout << "\n����� �� �������!\n\n";
                break;
            };
            PacketEdit(pipe_list, found_id, "�����");
            break;
        };
        case 4:
            std::cout << "\n������������ � ������� ����...\n\n";
            return;
        default:
            std::cout << "����������� �����. ���������� ��� ���\n\n";
            break;
        };
    };
};

void CSMenu(std::map<int, CS>& cs_list)
{
    while (1) {
        std::cout << "--------------------------------------\n";
        std::cout << "�������� �����:\n1. �������� ��\n2. ����� �� ��������\n3. ����� �� �������� �������� �����������������\n4. ����� � ������� ����\n";
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
            found_id = FoundName(cs_list, "��");
            if (!found_id.empty()) {
                PacketEdit(cs_list, found_id, "��");
            };
            break;
        };
        case 3:
        {
            if (cs_list.empty())
            {
                std::cout << "\n�� ���\n\n";
                break;
            };

            found_id.clear();
            std::cout << "\n������� ������� ����������������� �����: ";
            int percent = ProverkaNumber<int>();

            for (const auto& element : cs_list) {
                if (element.second.getUnusedPercent() == percent) {
                    found_id.push_back(element.first);
                };
            };
            if (found_id.empty()) {
                std::cout << "\n�� �� �������!\n\n";
                break;
            };
            PacketEdit(cs_list, found_id, "��");
            break;
        };
        case 4:
            std::cout << "\n������������ � ������� ����...\n\n";
            return;
        default:
            std::cout << "����������� �����. ���������� ��� ���\n\n";
            break;
        };
    };
};

void ViewAllObjects(const std::map<int, Pipe>& pipe_list, const std::map<int, CS>& cs_list)
{
    if (pipe_list.empty()) {
        std::cout << "\n���� ���\n";
    }
    else {
        std::cout << "\n��� �����:\n--------------------------------------\n";
        for (const auto& element : pipe_list) {
            std::cout << element.second << "--------------------------------------\n";
        };
    };

    if (cs_list.empty()) {
        std::cout << "�� ���\n\n";
    }
    else {
        std::cout << "\n��� ��:\n--------------------------------------\n";
        for (const auto& element : cs_list) {
            std::cout << element.second << "--------------------------------------\n";
        };
        std::cout << std::endl;
    };
};

void Save(const std::map<int, Pipe>& pipe_list, const std::map<int, CS>& cs_list)
{
    std::string file;
    std::cout << "\n������� �������� �����: ";
    getline(std::cin, file);

    std::ofstream save;
    save.open(file);
    if (save.is_open()) {
        if (!(pipe_list.empty())) {
            save << "�����\n";
            for (const auto& element : pipe_list) {
                save << element.second.getId() << "|" << element.second.getName() << "|" << element.second.getLength() << "|" << element.second.getDiameter() << "|" << element.second.getRepair() << "|" << std::endl;
            };
            std::cout << "\n������ ���� ��������!\n";
        }
        else {
            save << "���� ���\n";
            std::cout << "\n���� ���\n";
        };

        if (!(cs_list.empty())) {
            save << "��\n";
            for (const auto& element : cs_list) {
                save << element.second.getId() << "|" << element.second.getName() << "|" << element.second.getKCex() << "|" << element.second.getKCexInWork() << "|" << element.second.getType() << "|" << std::endl;
            };
            std::cout << "������ �� ��������!\n\n";
        }
        else {
            save << "�� ���";
            std::cout << "�� ���\n\n";
        };
    }
    else {
        std::cout << "\n������������ ��� �����!\n\n";
        return;
    };
};

void Upload(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list)
{
    std::string file;
    std::cout << "\n������� ��� �����: ";
    getline(std::cin, file);

    std::string line;
    std::string state = "None";
    std::ifstream upload(file);

    if (!(upload.is_open())) {
        std::cout << "\n���� '" << file << "' �� ������\n\n";
        return;
    };

    pipe_list.clear();
    cs_list.clear();

    while (getline(upload, line)) {
        if (line.empty() || line.find_first_not_of(' ') == std::string::npos) {
            continue;
        };

        if ("���� ���" == line) {
            std::cout << "\n���� ���\n";
            continue;
        }
        else if ("�����" == line) {
            state = "Trubs";
            continue;
        };

        if ("�� ���" == line) {
            std::cout << "�� ���\n";
            continue;
        }
        else if ("��" == line) {
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
        std::cout << "�������� �����:\n1. ���� ����\n2. ���� ��\n3. �������� ���� ��������\n4. ���������\n5. ���������\n9. �����\n";
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
            std::cout << "\n�������...\n";
            return;
        default:
            std::cout << "����������� �����. ���������� ��� ���\n\n";
            break;
        };
    };
};