#include <iostream>
#include <string>
#include <limits>
#include <clocale>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Pipe 
{
public:
    
    string name;
    float length;
    int diameter;
    bool repair;

};

class CS
{
public:

    string name;
    int k_cex;
    int k_cex_in_work;
    string type;

};

int ProverkaInt()
{
    string line;
    while (true) {
        getline(cin, line);
        try
        {
            for (char w : line) {
                string temp(1, w);
                stoi(temp);
            };

            int value = stoi(line);
            if (value <= 0) {
                throw invalid_argument("Number must be positive");
            };
            return value;
        }
        catch (const std::invalid_argument& e) {
            cout << "Ошибка!\nВведите ПОЛОЖИТЕЛЬНОЕ ЦЕЛОЕ ЧИСЛО: ";
        };
    };
};

float ProverkaFloat()
{
    string line;
    while (true) {
        getline(cin, line);
        try
        {
            int k = 0;
            for (char w : line) {
                if (w == ',' && k < 1) {
                    k++;
                    continue;
                };
                string temp(1, w);
                stoi(temp);
            };

            float value = stof(line);
            if (value <= 0) {
                throw invalid_argument("Number must be positive");
            };
            return value;
        }
        catch (const std::invalid_argument& e) {
            cout << "Ошибка!\nВведите ПОЛОЖИТЕЛЬНОЕ ЧИСЛО: ";
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

void AddPipe(map<int, Pipe>& pipe_list)
{
    Pipe newPipe;
    cout << "\nВведите название трубы: ";
    getline(cin, newPipe.name);

    cout << "Введите длину трубы (км): ";
    newPipe.length = ProverkaFloat();

    cout << "Введите диаметр трубы (мм): ";
    newPipe.diameter = ProverkaInt();

    string status;
    cout << "Труба на ремонте?(Yes/No): ";
    while (true) {
        cin >> status;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (status == "Yes") {
            newPipe.repair = true;
            break;
        }
        else if (status == "No") {
            newPipe.repair = false;
            break;
        }
        else {
            cout << "Ошибка! Введите 'Yes' или 'No': ";
        };
    };

    int ID = GetNextID(pipe_list);
    pipe_list[ID] = newPipe;
    cout << "\nНовая труба добавлена\n\n";

};

void AddCS(map<int, CS>& cs_list)
{
    CS newCS;
    cout << "\nВведите название КС: ";
    getline(cin, newCS.name);

    cout << "Введите общее количество цехов: ";
    newCS.k_cex = ProverkaInt();

    cout << "Введите количество цехов в работе: ";
    newCS.k_cex_in_work = ProverkaInt();
    if (newCS.k_cex_in_work > newCS.k_cex) {
        cout << "Ошибка! Количество цехов в работе не может быть больше общего количества цехов\nВведите корректное число: ";
        newCS.k_cex_in_work = ProverkaInt();
    };

    cout << "Введите тип КС: ";
    getline(cin, newCS.type);

    int ID = GetNextID(cs_list);
    cs_list[ID] = newCS;
    cout << "\nНовая КС добавлена\n\n";
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
            cout << "Название: " << element.second.name << endl;
            cout << "Длина (км): " << element.second.length << endl;
            cout << "Диаметр (мм): " << element.second.diameter << endl;
            if (element.second.repair == false) {
                cout << "В ремонте: Нет\n";
            }
            else if (element.second.repair == true) {
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
            cout << "Название: " << element.second.name << endl;
            cout << "Общее количество цехов: " << element.second.k_cex << endl;
            cout << "Количество цехов в работе: " << element.second.k_cex_in_work << endl;
            cout << "Тип: " << element.second.type << endl;
            cout << "--------------------------------------\n";
        };
        cout << endl;
    };
};

void EditPipe(vector<int>& IDS, map<int, Pipe>& pipe_list)
{
    if (IDS.empty()) {
        cout << "\nТРУБ НЕТ\n\n";
        return;
    }

    string status;
    cout << "\nТруба/ы в ремонте?(Yes/No): ";
    while (true) {
        cin >> status;
        if (status == "Yes") {
            for (size_t i = 0; i < IDS.size(); i++) {
                pipe_list[IDS[i]].repair = true;
            };
            cout << "Статус 'в ремонте' сменен на 'Да'\n\n";
            break;
        }
        else if (status == "No") {
            for (size_t i = 0; i < IDS.size(); i++) {
                pipe_list[IDS[i]].repair = false;
            };
            cout << "Статус 'в ремонте' сменен на 'Нет'\n\n";
            break;
        }
        else {
            cout << "Ошибка! Введите 'Yes' или 'No': ";
        };
    };
};

void PaketEditPipe(vector<int>& IDS, map<int, Pipe>& pipe_list)
{
    int i;
    string line;
    vector<int> ID;
    while (1) {
        cout << "--------------------------------------\n";
        cout << "Выберите опцию:\n1. Редактировать все найденные\n2. Выбрать несколько или одну труб(у) в списке найденных\n3. Вернутся к поиску\n";
        cout << "--------------------------------------\n\n";
        int option;
        option = ProverkaInt();

        switch (option)
        {
        case 1:
            EditPipe(IDS, pipe_list);
            break;
        case 2: 
        {
            cout << "Введите ID труб/ы в списке найденных: ";
            getline(cin, line);
            stringstream ss(line);
            string word;

            while (ss >> word) {
                bool param = false;
                try {
                    stoi(word);
                }
                catch (const std::invalid_argument& e) {
                    cout << "Ошибка: '" << word << "' не является числом!" << endl;
                };

                for (int i : IDS)
                {
                    if (i == stoi(word)) {
                        ID.push_back(stoi(word));
                        param = true;
                    };
                };
                if (param == false) {
                    cout << "ID:" << word << " нету среди найденных" << endl;
                };
            };

            EditPipe(ID, pipe_list);
            break;
        };
        case 3:
            return;
        default:
            cout << "Неизвестная опция. Попробуйте еще раз\n\n";
        };
    };
};

void SearchPipe(map<int, Pipe>& pipe_list)
{
    vector<int> IDS;
    string name1;
    int i = 0;
    while (1) {
        while (1) {
            cout << "--------------------------------------\n";
            cout << "Выберите опцию:\n1. Найти трубу по названию\n2. Найти трубу по признаку 'в ремонте'\n3. Вернутся в главное меню\n";
            cout << "--------------------------------------\n\n";
            int option;
            option = ProverkaInt();

            switch (option)
            {
            case 1:
                IDS.clear();
                cout << "Введите название трубы: ";
                getline(cin, name1);
                cout << "\nНайденные трубы:\n";
                for (auto& element : pipe_list) {
                    if (name1 == element.second.name) {
                        IDS.push_back(element.first);
                        cout << i + 1 << ". " <<  element.second.name << " " << "[ID:" << element.first << "]" << endl;
                        i++;
                    };
                };
                cout << endl;
                PaketEditPipe(IDS, pipe_list);
                break;
            case 2:
                break;
            case 3:
                return;
            default:
                cout << "Неизвестная опция. Попробуйте еще раз\n\n";
                break;
            };
        };
    };
};

void Save(const map<int, Pipe>& pipe_list, const map<int, CS>& cs_list)
{
    string file;
    cout << "Введите название файла: ";
    cin >> file;

    ofstream save;
    save.open(file);
    if (save.is_open()) {
        if (!(pipe_list.empty())) {
            save << "ТРУБЫ\n";
            for (const auto& element : pipe_list) {
                save << element.first << "|" << element.second.name << "|" << element.second.length << "|" << element.second.diameter << "|" << element.second.repair << "|" << endl;
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
                save << element.first << "|" << element.second.name << "|" << element.second.k_cex << "|" << element.second.k_cex_in_work << "|" << element.second.type << "|" << endl;
            };
            cout << "Список КС сохранен!\n\n";
        }
        else {
            save << "КС НЕТ";
            cout << "КС НЕТ\n\n";
        };
    }
    else {
        cout << "Недопустимое имя файла!\n\n";
        return;
    };
};

void Upload(map<int, Pipe>& pipe_list, map<int, CS>& cs_list)
{
    string file;
    cout << "Введите имя файла: ";
    cin >> file;

    string line;
    string state = "None";
    ifstream upload(file);

    if (!(upload.is_open())) {
        cout << "\nФайл '" << file << "' не найден\n";
        upload.close();
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
            cout << "КС НЕТ\n\n";
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
            Pipe newPipe;
            newPipe.name = sub[1];
            newPipe.length = stof(sub[2]);
            newPipe.diameter = stoi(sub[3]);
            if (stoi(sub[4]) == 1) {
                newPipe.repair = true;
            }
            else {
                newPipe.repair = false;
            };

            pipe_list.emplace(ID, newPipe);
        };

        if (state == "CS") {
            int ID = stoi(sub[0]);
            CS newCS;
            newCS.name = sub[1];
            newCS.k_cex = stoi(sub[2]);
            newCS.k_cex_in_work = stoi(sub[3]);
            newCS.type = sub[4];

            cs_list.emplace(ID, newCS);
        };
    };
    upload.close();
};

void Menu(map<int, Pipe>& pipe_list, map<int, CS>& cs_list)
{
    while (1) {
        cout << "--------------------------------------\n";
        cout << "Выберите опцию:\n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Редактировать трубу\n5. Редактировать КС\n6. Сохранить\n7. Загрузить\n8. Выход\n";
        cout << "--------------------------------------\n\n";
        int option;
        option = ProverkaInt();

        switch (option) 
        {
        case 1:
            AddPipe(pipe_list);
            break;
        case 2:
            AddCS(cs_list);
            break;
        case 3:
            ViewAllObjects(pipe_list, cs_list);
            break;
        case 4:
            SearchPipe(pipe_list);
            break;
        case 5:
            break;
        case 6:
            Save(pipe_list, cs_list);
            break;
        case 7:
            Upload(pipe_list, cs_list);
            break;
        case 8:
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