#include <iostream>
#include <string>
#include <limits>
#include <clocale>
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
    int value;
    while (!(cin >> value) || value <= 0) {
        cout << "Ошибка! Введите ПОЛОЖИТЕЛЬНОЕ ЦЕЛОЕ ЧИСЛО: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    };
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
};

float ProverkaFloat()
{
    float value;
    while (!(cin >> value) || value <= 0) {
        cout << "Ошибка! Введите ПОЛОЖИТЕЛЬНОЕ ЧИСЛО: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    };
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
};

void Menu()
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
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
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
   Menu();
}

