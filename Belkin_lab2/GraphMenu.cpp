#include "GraphMenu.h"
#include "MenuFunctions.h"
#include "Validation.h"
#include "Utils.h"
#include "Graph.h"
#include <vector>

bool isPipeUsed(const std::map<int, Node*>& graph, int pipe_id)
{
    for (const auto& node_pair : graph) {
        Node* node = node_pair.second;

        for (const Edge* edge : node->edges) {
            if (edge->pipe && edge->pipe->getId() == pipe_id) {
                return true;
            };
        };

        for (const auto& parent_pair : node->parents) {
            const Edge* edge = parent_pair.second;
            if (edge->pipe && edge->pipe->getId() == pipe_id) {
                return true;
            };
        };
    };
    return false;
};

Node* addOrGetNode(std::map<int, Node*>& graph, int value, std::map<int, CS>& cs_list)
{
    if (value == -1) { return nullptr; }
    if (graph.find(value) != graph.end()) {
        return graph[value];
    };
    Node* node = new Node(value, &cs_list.at(value));
    graph[value] = node;
    return node;
};

void CreateGraph(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::map<int, Node*>& graph, std::vector<int>& selected_data)
{
    Node* node = addOrGetNode(graph, selected_data[0], cs_list);
    Node* adjacentNode = addOrGetNode(graph, selected_data[1], cs_list);

    Edge* edge = new Edge(adjacentNode, &pipe_list.at(selected_data[2]), pipe_list[selected_data[2]].getLength());
    node->edges.push_back(edge);
    adjacentNode->parents[node] = edge;
};

std::vector<int> FoundDiameter(std::map<int, Pipe>& pipe_list, std::map<int, Node*>& graph)
{
    std::vector<int> found_id;

    std::cout << "\nВыберите диаметр трубы (500 мм, 700 мм, 1000 мм, 1400 мм): ";
    int input_diameter;
    do {
        input_diameter = ProverkaNumber<int>();
        if (input_diameter != 500 && input_diameter != 700 && input_diameter != 1000 && input_diameter != 1400)
        {
            std::cout << "Выберите корректное значение (500, 700, 1000 или 1400): ";
        };
    } while (input_diameter != 500 && input_diameter != 700 && input_diameter != 1000 && input_diameter != 1400);

    bool is_used;
    for (const auto& element : pipe_list)
    {
        is_used = isPipeUsed(graph, element.first);
        if (element.second.getDiameter() == input_diameter && is_used == false)
        {
            found_id.push_back(element.first);
        };
    };
    if (found_id.empty()) {
        std::cout << "\nТрубы с таким диаметром найдены!\n";
        std::cout << "Перейдем к созданию трубы...\n";
        AddPipe(pipe_list);
        pipe_list.rbegin()->second.setDiameter(input_diameter);
        std::cout << pipe_list.rbegin()->second;
        found_id.push_back(pipe_list.rbegin()->first);
    };

    return found_id;
};

int isCSReal(std::map<int, CS>& cs_list)
{
    bool is_selected = true;
    int cs_id;
    do {
        cs_id = ProverkaNumber<int>();
        if (cs_list.find(cs_id) != cs_list.end()) {
            is_selected = false;
        }
        else {
            std::cout << "КС с ID " << cs_id << " не существует\nВведите существующий ID КС: ";
        };
    } while (is_selected);
    
    return cs_id;
};

void FunctionToCreateGraph(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::map<int, Node*>& graph)
{
    std::vector<int> selected_data;

    if (pipe_list.size() < 1 || cs_list.size() < 2)
    {
        std::cout << "\nСлишком мало труб и кс для создания графа\n";
        return;
    };

    std::vector<int> found_id = FoundDiameter(pipe_list, graph);
    DisplayFound(pipe_list, found_id, "трубы");

    std::cout << "Введите ID трубы: ";
    int pipe_id;
    bool is_selected;
    do {
        is_selected = true;
        pipe_id = ProverkaNumber<int>();
        for (auto& found_pipe_id : found_id)
        {
            if (pipe_id == found_pipe_id) {
                is_selected = false;
            };
        };
        if (is_selected) {
            std::cout << "Введите ID трубы в списке найденных труб: ";
        }
    } while (is_selected);

    is_selected = true;
    int cs_start;
    int cs_end;
    do {
        std::cout << "\nВведите ID КС от которой будет идти труба: ";
        cs_start = isCSReal(cs_list);
        std::cout << "Введите ID КС к которой будет идти труба: ";
        cs_end = isCSReal(cs_list);
        if (cs_list[cs_start].getType() == cs_list[cs_end].getType()) {
            is_selected = false;
            break;
        }
        std::cout << "\nТип станции входа [ID:" << cs_start << "]: " << cs_list[cs_start].getType() << "\nТип станции выхода[ID:" << cs_end << "]: " << cs_list[cs_end].getType() << std::endl;
        std::cout << "Введите станции с одинаковым типом\n";
    } while (is_selected);
    
    selected_data.push_back(cs_start);
    selected_data.push_back(cs_end);
    selected_data.push_back(pipe_id);

    CreateGraph(pipe_list, cs_list, graph, selected_data);

    std::cout << "\nГраф добавлен: " << "CS [ID:" << cs_start << "] ----- (Pipe [ID:" << pipe_id << "]) -----> CS [ID:" << cs_end << "]\n";
};

void GraphMenu(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::map<int, Node*>& graph)
{
    while (1) {
        std::cout << "\n--------------------------------------\n";
        std::cout << "Выберите опцию:\n1. Добавить граф\n9. Выход\n";
        std::cout << "--------------------------------------\n\n";
        int option;
        option = ProverkaNumber<int>();

        switch (option) {
        case 1:
            FunctionToCreateGraph(pipe_list,cs_list, graph);
            break;
        case 9:
            std::cout << "\nВыходим из меню графов\n\n";
            return;
        default:
            std::cout << "Неизвестная опция. Попробуйте еще раз\n\n";
            break;
        };
    };
};