#include <iostream>
#include <string>
#include <limits>
#include <clocale>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "Pipe.h"
#include "CS.h"
using namespace std;

template <typename T>
T ProverkaNumber()
{
    string line;
    while (true) {
        getline(cin, line);
        try
        {
            int k = 0;
            for (char w : line) {
                if constexpr (is_floating_point_v<T>) {
                    if (w == ',') {
                        k++;
                        if (k > 1) throw invalid_argument("Multiple decimals");
                        continue;
                    };
                };
                if (!isdigit(w)) {
                    throw invalid_argument("Invalid character");
                };
            };
            T value;
            if constexpr (is_integral_v<T>) {
                value = stoi(line);
            }
            else {
                value = stof(line);
            };
            if (value <= 0) {
                throw invalid_argument("Number must be positive");
            };
            return value;
        }
        catch (const std::invalid_argument& e) {
            cout << "Ошибка!\nВведите корректное число: ";
        };
    };
};

bool CheckYesNo() {
    string word;
    while (true) {
        getline(cin, word);
        if (word == "Yes" || word == "y" || word == "yes") {
            return true;
        }
        else if (word == "No" || word == "n" || word == "no") {
            return false;
        }
        else {
            cout << "Введите \"Yes\" или \"No\": ";
        };
    };
};

template<typename T>
int GetNextID(const map<int, T>& container)
{
    if (container.empty()) {
        return 1;
    }
    else {
        return container.rbegin()->first + 1;
    };
};

vector<int> Packet(const vector<int>& found_id)
{
    vector<int> select_id;
    string line;
    getline(cin, line);
    stringstream ss(line);
    string word;

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
                cout << "ID:" << word << " нету среди найденных" << endl;
            };
        }
        catch (const std::invalid_argument& e) {
            cout << "Ошибка: '" << word << "' не является числом!" << endl;
        };
    };

    return select_id;
};

template<typename T>
void Delete(map<int, T>& container, vector<int>& found_id, vector<int> select_id)
{
    for (int i : select_id) {
        container.erase(i);
    };

    for (int i : found_id) {
        for (int j : select_id) {
            if (i == j) {
                found_id.erase(remove(found_id.begin(), found_id.end(), i), found_id.end());
            };
        };
    };
};

template <typename T>
void DisplayFound(const map<int, T>& container, const vector<int>& found_id, string name)
{

    cout << "\nНайденные " << name << ":\n--------------------------------------\n";
    if constexpr (is_same_v<T, Pipe>) {
        for (int i : found_id) {
            const Pipe& pipe = container.find(i)->second;
            cout << pipe.getName() << " [ID:" << pipe.getId() << "] Статус в ремонте: ";
            if (pipe.getRepair() == true) {
                cout << "ДА" << endl;
            }
            else {
                cout << "НЕТ" << endl;
            };
        };
    }
    else if constexpr (is_same_v<T, CS>) {
        for (int i : found_id) {
            const CS& cs = container.find(i)->second;
            cout << cs.getName() << " [ID:" << cs.getId() << "] Процент незадействованных цехов в работе: " << cs.getUnusedPercent() << "% (" << cs.getKCexInWork() << "/" << cs.getKCex() << ")" << endl;
        };
    };
    cout << "--------------------------------------\n\n";
};

template <typename T>
vector<int> FoundName(map<int, T>& container, string nameClass)
{
    vector<int> found_id;
    if (container.empty())
    {
        cout << "\nЭлементов нет\n\n";
        return found_id;
    };

    cout << "\nВведите название " << nameClass << ": ";
    string name;
    getline(cin, name);

    for (const auto& element : container) {
        if (element.second.getName() == name) {
            found_id.push_back(element.first);
        };
    };
    if (found_id.empty()) {
        cout << "\n" << nameClass << " не найдены!\n\n";
        return found_id;
    };
    return found_id;
};

void AddPipe(map<int, Pipe>& pipe_list)
{

    string name;
    cout << "\nВведите название трубы: ";
    getline(cin, name);

    cout << "Введите длину трубы (км): ";
    float length = ProverkaNumber<float>();

    cout << "Введите диаметр трубы (мм): ";
    int diameter = ProverkaNumber<int>();

    string status;
    cout << "Труба на ремонте?(Yes/No): ";
    bool repair = CheckYesNo();

    int ID = GetNextID(pipe_list);
    Pipe newPipe(ID, name, length, diameter, repair);
    pipe_list[ID] = newPipe;
    cout << "\nНовая труба добавлена\n\n";

};

void EditPipe(map<int, Pipe>& pipe_list, vector<int>& found_id)
{
    if (found_id.empty()) {
        cout << "\nТруб нет!\n";
        return;
    };

    string status;
    cout << "\nТруба/ы в ремонте?(Yes/No): ";
    while (true) {
        getline(cin, status);
        if (status == "Yes" || status == "y" || status == "yes") {
            for (int i : found_id) {
                pipe_list[i].setRepair(true);
            };
            cout << "\nСтатус \"в ремонте\" сменен на \"Да\"\n";
            break;
        }
        else if (status == "No" || status == "n" || status == "no") {
            for (int i : found_id) {
                pipe_list[i].setRepair(false);
            };
            cout << "\nСтатус \"в ремонте\" сменен на \"Нет\"\n";
            break;
        }
        else {
            cout << "Ошибка! Введите \"Yes\" или \"No\": ";
        };
    };
};

void AddCS(map<int, CS>& cs_list)
{
    
    string name;
    cout << "\nВведите название КС: ";
    getline(cin, name);

    cout << "Введите общее количество цехов: ";
    int k_cex = ProverkaNumber<int>();

    cout << "Введите количество цехов в работе: ";
    int k_cex_in_work = ProverkaNumber<int>();
    if (k_cex_in_work > k_cex) {
        cout << "Ошибка! Количество цехов в работе не может быть больше общего количества цехов\nВведите корректное число: ";
        k_cex_in_work = ProverkaNumber<int>();
    };

    string type;
    cout << "Введите тип КС: ";
    getline(cin, type);

    int ID = GetNextID(cs_list);
    CS newCS(ID, name, k_cex, k_cex_in_work, type);
    cs_list[ID] = newCS;
    cout << "\nНовая КС добавлена\n\n";
};

void EditCS(map<int, CS>& cs_list, vector<int>& found_id)
{
    if (found_id.empty()) {
        cout << "\nКС нет!\n";
        return;
    };

    while (1)
    {
        DisplayFound(cs_list, found_id, "КС");
        cout << "--------------------------------------\n";
        cout << "Выберите опцию:\n1. Запустить цеха\n2. Остановить цеха\n3. Вернутся обратно\n";
        cout << "--------------------------------------\n\n";
        int option = ProverkaNumber<int>();

        switch (option)
        {
        case 1:
        {
            cout << "\nВведите сколько цехов запустить: ";
            int count = ProverkaNumber<int>();
            for (auto& element : found_id) {
                if (!cs_list[element].startWorkshops(count)) {
                    cout << "\nНельзя запустить больше цехов чем доступно!\n";
                    break;
                };
            };
            break;
        };
        case 2:
        {
            cout << "\nВведите сколько цехов остановить: ";
            int count = ProverkaNumber<int>();
            for (auto& element : found_id) {
                if (!cs_list[element].stopWorkshops(count)) {
                    cout << "\nНельзя остановить больше цехов чем работает!\n";
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

template <typename T>
void PacketEdit(map<int, T>& container, vector<int>& found_id, string name)
{
    while (1) {
        DisplayFound(container, found_id, name);
        cout << "--------------------------------------\n";
        cout << "Выберите опцию:\n1. Редактировать все найденные\n2. Редактировать один или несколько элементов в списке найденных\n3. Удалить все найденные\n4. Удалить один или несколько элементов в списке найденных\n5. Вернутся обратно\n";
        cout << "--------------------------------------\n\n";
        int option = ProverkaNumber<int>();

        switch (option)
        {
        case 1:
            if constexpr (is_same_v<T, Pipe>) {
                EditPipe(container, found_id);
            };
            if constexpr (is_same_v<T, CS>) {
                EditCS(container, found_id);
            };
            break;
        case 2:
        {
            cout << "\nВведите ID элемента(-ов) через пробел : ";
            vector<int> select_id = Packet(found_id);
            if constexpr (is_same_v<T, Pipe>) {
                EditPipe(container, select_id);
            };
            if constexpr (is_same_v<T, CS>) {
                EditCS(container, select_id);
            };
            break;
        };
        case 3:
            if (found_id.empty()) {
                cout << "\nЭлементов нет!\n";
                break;
            };
            Delete(container, found_id, found_id);
            cout << "\nЭлементы удалены!\n\n";
            return;
        case 4:
        {
            cout << "\nВведите ID элемента(-ов) через пробел: ";
            vector<int> select_id = Packet(found_id);

            if (select_id.empty()) {
                cout << "\nЭлементов нет!\n";
                break;
            };
            Delete(container, found_id, select_id);
            cout << "\nЭлементы удалены!\n";
            break;
        };
        case 5:
            cout << endl;
            return;
        default:
            cout << "Неизвестная опция. Попробуйте еще раз\n\n";
        };
    };
};

void PipeMenu(map<int, Pipe>& pipe_list)
{
    while (1) {
        cout << "--------------------------------------\n";
        cout << "Выберите опцию:\n1. Добавить трубу\n2. Найти по названию\n3. Найти по признаку \"в ремонте\"\n4. Выйти в главное меню\n";
        cout << "--------------------------------------\n\n";
        int option = ProverkaNumber<int>();
        vector<int> found_id;

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
                cout << "\nТруб нет\n\n";
                break;
            };

            found_id.clear();
            cout << "\nИскать трубы в ремонте(Yes/No): ";
            string word;
            bool status = CheckYesNo();

            for (const auto& element : pipe_list) {
                if (element.second.getRepair() == status) {
                    found_id.push_back(element.first);
                };
            };
            if (found_id.empty()) {
                cout << "\nТрубы не найдены!\n\n";
                break;
            };
            PacketEdit(pipe_list, found_id, "трубы");
            break;
        };
        case 4:
            cout << "\nВозвращаемся в главное меню...\n\n";
            return;
        default:
            cout << "Неизвестная опция. Попробуйте еще раз\n\n";
            break;
        };
    };
};

void CSMenu(map<int, CS>& cs_list)
{
    while (1) {
        cout << "--------------------------------------\n";
        cout << "Выберите опцию:\n1. Добавить КС\n2. Найти по названию\n3. Найти по признаку проценту незадействованных\n4. Выйти в главное меню\n";
        cout << "--------------------------------------\n\n";
        int option = ProverkaNumber<int>();
        vector<int> found_id;

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
                cout << "\nКС нет\n\n";
                break;
            };

            found_id.clear();
            cout << "\nВведите процент незадействованных цехов: ";
            int percent = ProverkaNumber<int>();

            for (const auto& element : cs_list) {
                if (element.second.getUnusedPercent() == percent) {
                    found_id.push_back(element.first);
                };
            };
            if (found_id.empty()) {
                cout << "\nКС не найдены!\n\n";
                break;
            };
            PacketEdit(cs_list, found_id, "КС");
            break;
        };
        case 4:
            cout << "\nВозвращаемся в главное меню...\n\n";
            return;
        default:
            cout << "Неизвестная опция. Попробуйте еще раз\n\n";
            break;
        };
    };
};

void ViewAllObjects(const map<int, Pipe>& pipe_list, const map<int, CS>& cs_list)
{
    if (pipe_list.empty()) {
        cout << "\nТРУБ НЕТ\n";
    }
    else {

        cout << "\nВСЕ ТРУБЫ:\n--------------------------------------\n";

        for (const auto& element : pipe_list) {
            cout << "Труба [ID:" << element.first << "]" << endl;
            cout << "Название: " << element.second.getName() << endl;
            cout << "Длина (км): " << element.second.getLength() << endl;
            cout << "Диаметр (мм): " << element.second.getDiameter() << endl;
            if (element.second.getRepair() == false) {
                cout << "В ремонте: Нет\n";
            }
            else if (element.second.getRepair() == true) {
                cout << "В ремонте: Да\n";
            };
            cout << "--------------------------------------\n";
        };
    };

    if (cs_list.empty()) {
        cout << "КС НЕТ\n\n";
    }
    else {

        cout << "\nВСЕ КС:\n--------------------------------------\n";

        for (const auto& element : cs_list) {
            cout << "КС [ID:" << element.first << "]" << endl;
            cout << "Название: " << element.second.getName() << endl;
            cout << "Общее количество цехов: " << element.second.getKCex() << endl;
            cout << "Количество цехов в работе: " << element.second.getKCexInWork() << endl;
            cout << "Тип: " << element.second.getType() << endl;
            cout << "--------------------------------------\n";
        };
        cout << endl;
    };
};

void Save(const map<int, Pipe>& pipe_list, const map<int, CS>& cs_list)
{
    string file;
    cout << "\nВведите название файла: ";
    getline(cin, file);

    ofstream save;
    save.open(file);
    if (save.is_open()) {
        if (!(pipe_list.empty())) {
            save << "ТРУБЫ\n";
            for (const auto& element : pipe_list) {
                save << element.second.getId() << "|" << element.second.getName() << "|" << element.second.getLength() << "|" << element.second.getDiameter() << "|" << element.second.getRepair() << "|" << endl;
            };
            cout << "\nСписок труб сохранен!\n";
        }
        else {
            save << "ТРУБ НЕТ\n";
            cout << "\nТРУБ НЕТ\n";
        };

        if (!(cs_list.empty())) {
            save << "КС\n";
            for (const auto& element : cs_list) {
                save << element.second.getId() << "|" << element.second.getName() << "|" << element.second.getKCex() << "|" << element.second.getKCexInWork() << "|" << element.second.getType() << "|" << endl;
            };
            cout << "Список КС сохранен!\n\n";
        }
        else {
            save << "КС НЕТ";
            cout << "КС НЕТ\n\n";
        };
    }
    else {
        cout << "\nНедопустимое имя файла!\n\n";
        return;
    };
};

void Upload(map<int, Pipe>& pipe_list, map<int, CS>& cs_list)
{
    string file;
    cout << "\nВведите имя файла: ";
    getline(cin, file);

    string line;
    string state = "None";
    ifstream upload(file);

    if (!(upload.is_open())) {
        cout << "\nФайл '" << file << "' не найден\n\n";
        return;
    };

    pipe_list.clear();
    cs_list.clear();

    while (getline(upload, line)) {

        if (line.empty() || line.find_first_not_of(' ') == string::npos) {
            continue;
        };

        if ("ТРУБ НЕТ" == line) {
            cout << "\nТРУБ НЕТ\n";
            continue;
        }
        else if ("ТРУБЫ" == line) {
            state = "Trubs";
            continue;
        };

        if ("КС НЕТ" == line) {
            cout << "КС НЕТ\n";
            continue;
        }
        else if ("КС" == line) {
            state = "CS";
            continue;
        };

        vector<size_t> pos = { 0 };
        for (size_t i = 0; i < 5; i++) {
            size_t found_pos = line.find('|', pos[i]);
            pos.push_back(found_pos + 1);
        };

        vector<string> sub;
        for (size_t i = 0; i < (pos.size() - 1); i++) {
            string found_sub = line.substr(pos[i], pos[i + 1] - pos[i] - 1);
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
    cout << endl;
    upload.close();
};

void Menu(map<int, Pipe>& pipe_list, map<int, CS>& cs_list)
{
    while (1) {
        cout << "--------------------------------------\n";
        cout << "Выберите опцию:\n1. Меню труб\n2. Меню КС\n3. Просмотр всех объектов\n4. Сохранить\n5. Загрузить\n9. Выход\n";
        cout << "--------------------------------------\n\n";
        int option;
        option = ProverkaNumber<int>();

        switch (option)
        {
        case 1:
            cout << endl;
            PipeMenu(pipe_list);
            break;
        case 2:
            cout << endl;
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
            cout << "\nВыходим...\n";
            return;
        default:
            cout << "Неизвестная опция. Попробуйте еще раз\n\n";
            break;
        };
    };
};

int main()
{
    setlocale(LC_ALL, "");
    map<int, Pipe> pipe_list;
    map<int, CS> cs_list;
    Menu(pipe_list, cs_list);
}
