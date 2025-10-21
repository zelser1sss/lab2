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
#include "Validation.h"
#include "Utils.h"
#include "MenuFunctions.h"
#include "Logger.h"
using namespace std;


int main()
{
    setlocale(LC_ALL, "");
    Logger::log("=== СИСТЕМА УПРАВЛЕНИЯ ТРУБОПРОВОДАМИ ЗАПУЩЕНА ===");

    map<int, Pipe> pipe_list;
    map<int, CS> cs_list;
    Menu(pipe_list, cs_list);

    Logger::log("=== ПРОГРАММА ЗАВЕРШЕНА ===");
}