#include "GraphMenu.h"
#include "MenuFunctions.h"
#include "Validation.h"
#include "Utils.h"
#include "Graph.h"
#include <vector>
#include <unordered_set>

bool isPipeUsed(const std::unordered_map<int, Node*>& graph, int pipe_id)
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

bool isCSUsed(const std::unordered_map<int, Node*>& graph, int cs_id)
{
    for (const auto& node_pair : graph)
    {
        Node* node = node_pair.second;
        if (node->cs->getId() == cs_id) {
            return true;
        };
    };
    return false;
};

Node* addOrGetNode(std::unordered_map<int, Node*>& graph, int value, std::map<int, CS>& cs_list)
{
    if (value == -1) { return nullptr; }
    if (graph.find(value) != graph.end()) {
        return graph[value];
    };
    Node* node = new Node(value, &cs_list.at(value));
    graph[value] = node;
    return node;
};

void CreateGraph(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph, std::vector<int>& selected_data)
{
    Node* node = addOrGetNode(graph, selected_data[0], cs_list);
    Node* adjacentNode = addOrGetNode(graph, selected_data[1], cs_list);

    Edge* edge = new Edge(adjacentNode, &pipe_list.at(selected_data[2]), pipe_list[selected_data[2]].getLength());
    node->edges.push_back(edge);
    adjacentNode->parents[node] = edge;
};

std::vector<int> FoundDiameter(std::map<int, Pipe>& pipe_list, std::unordered_map<int, Node*>& graph)
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

void RemoveEdge(std::unordered_map<int, Node*>& graph, std::vector<int>& pipe_id)
{
    std::unordered_set<int> pipe_set(pipe_id.begin(), pipe_id.end());
    std::unordered_set<Edge*> edges_to_delete;

    for (const auto& node_pair : graph) {
        Node* node = node_pair.second;

        auto parents_it = node->parents.begin();
        while (parents_it != node->parents.end())
        {
            if (pipe_set.count(parents_it->second->pipe->getId()))
            {
                parents_it = node->parents.erase(parents_it);
            }
            else {
                ++parents_it;
            };
        };

        auto edge_it = node->edges.begin();
        while (edge_it != node->edges.end())
        {
            if (pipe_set.count((*edge_it)->pipe->getId()))
            {
                edges_to_delete.insert(*edge_it);
                edge_it = node->edges.erase(edge_it);
            }
            else {
                ++edge_it;
            };
        };
    };

    for (Edge* edge : edges_to_delete) {
        delete edge;
    };
};

void RemoveNode(std::unordered_map<int, Node*>& graph, std::vector<int>& cs_ids)
{
    std::unordered_set<int> cs_set(cs_ids.begin(), cs_ids.end());
    std::vector<int> edges_ids;

    for (auto& node_pair : graph) {
        Node* node = node_pair.second;

        auto parents_id = node->parents.begin();
        while (parents_id != node->parents.end()) {
            if (cs_set.count(parents_id->first->cs->getId())) {
                edges_ids.push_back(parents_id->second->pipe->getId());
                parents_id = node->parents.erase(parents_id);
            }
            else {
                ++parents_id;
            };
        };

        if (cs_set.count(node_pair.first)) {
            for (Edge* edge : node_pair.second->edges)
            {
                edges_ids.push_back(edge->pipe->getId());
            };
        };
    };

    RemoveEdge(graph, edges_ids);

    for (int cs_id : cs_set) {
        auto it = graph.find(cs_id);
        if (it != graph.end()) {
            delete it->second;  
            graph.erase(it);    
        }
    }
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

void FunctionToCreateGraph(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph)
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

void FunctionToRemoveEdge(std::unordered_map<int, Node*>& graph)
{
    bool is_selected = true;
    int pipe_id;
    do {
        std::cout << "\nВведите ID трубы, которую хотите удалить из графа: ";
        pipe_id = ProverkaNumber<int>();
        if (isPipeUsed(graph, pipe_id)) {
            is_selected = false;
        }
        else {
            std::cout << "Труба не используется в графе!\n";
        };
    } while (is_selected);

    std::vector<int> pipe_ids;
    pipe_ids.push_back(pipe_id);
    RemoveEdge(graph, pipe_ids);
    
    std::cout << "\nТруба [ID:" << pipe_id << "] удалена из графа\n";
};

void FunctionToRemoveNode(std::unordered_map<int, Node*>& graph)
{
    bool is_selected = true;
    int cs_id;
    do {
        std::cout << "\nВведите ID КС, которую хотите удалить из графа: ";
        cs_id = ProverkaNumber<int>();
        if (isCSUsed(graph, cs_id)) {
            is_selected = false;
        }
        else {
            std::cout << "КС не используется в графе!\n";
        };
    } while (is_selected);

    std::vector<int> cs_ids;
    cs_ids.push_back(cs_id);
    RemoveNode(graph, cs_ids);

    std::cout << "\nКС и инцидентные к ним трубы [ID:" << cs_id << "] удалены из графа\n";
};

void GraphMenu(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph)
{
    while (1) {
        std::cout << "\n--------------------------------------\n";
        std::cout << "Выберите опцию:\n1. Добавить граф\n2. Удалить трубу из графа\n3. Удалить КС из графа\n9. Выход\n";
        std::cout << "--------------------------------------\n\n";
        int option;
        option = ProverkaNumber<int>();

        switch (option) {
        case 1:
            FunctionToCreateGraph(pipe_list,cs_list, graph);
            break;
        case 2:
            FunctionToRemoveEdge(graph);
            break;
        case 3:
            FunctionToRemoveNode(graph);
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