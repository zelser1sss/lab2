#include "GraphOperations.h"
#include "MenuFunctions.h"

bool isUsedInGraph(const std::unordered_map<int, Node*>& graph, int id, std::string name_class)
{
    for (const auto& node_pair : graph) {
        Node* node = node_pair.second;

        if (name_class == "Pipe") {
            for (const Edge* edge : node->getEdges()) {
                if (edge->getPipe()->getId() == id) {
                    return true;
                };
            };

            for (const auto& parent_pair : node->getParents()) {
                const Edge* edge = parent_pair.second;
                if (edge->getPipe()->getId() == id) {
                    return true;
                };
            };
        }
        else if (name_class == "CS") {
            if (node->getCS()->getId() == id) {
                return true;
            };
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
    node->getEdges().push_back(edge);
    adjacentNode->getParents()[node] = edge;
};

int FoundDiameter(std::map<int, Pipe>& pipe_list, std::unordered_map<int, Node*>& graph)
{
    std::vector<int> found_id;

    std::cout << "\nВыберите диаметр трубы (530 мм, 720 мм, 1020 мм, 1220 мм, 1420 мм): ";
    int input_diameter;
    do {
        input_diameter = ProverkaNumber<int>();
        if (input_diameter != 530 && input_diameter != 720 && input_diameter != 1020 && input_diameter != 1220 && input_diameter != 1420)
        {
            std::cout << "Выберите корректное значение (530, 720, 1020, 1220 или 1420): ";
        };
    } while (input_diameter != 530 && input_diameter != 720 && input_diameter != 1020 && input_diameter != 1220 && input_diameter != 1420);

    return FoundObject(pipe_list, graph, input_diameter, "трубы");
};

void FoundType(std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph, int& cs_start, int& cs_end)
{
    std::cout << "Введите ID начальной КС: ";
    cs_start = isReal(cs_list, "КС");

    std::cout << "Тип выбранной станции: " << cs_list[cs_start].getType() << std::endl;

    cs_end = FoundObject(cs_list, graph, cs_start, "КС");
};

void RemoveEdge(std::unordered_map<int, Node*>& graph, std::vector<int>& pipe_id)
{
    std::unordered_set<int> pipe_set(pipe_id.begin(), pipe_id.end());
    std::unordered_set<Edge*> edges_to_delete;

    for (const auto& node_pair : graph) {
        Node* node = node_pair.second;

        auto parents_it = node->getParents().begin();
        while (parents_it != node->getParents().end())
        {
            if (pipe_set.count(parents_it->second->getPipe()->getId()))
            {
                parents_it = node->getParents().erase(parents_it);
            }
            else {
                ++parents_it;
            };
        };

        auto edge_it = node->getEdges().begin();
        while (edge_it != node->getEdges().end())
        {
            if (pipe_set.count((*edge_it)->getPipe()->getId()))
            {
                edges_to_delete.insert(*edge_it);
                edge_it = node->getEdges().erase(edge_it);
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
    std::unordered_set<int> pipes_to_remove;

    for (auto& node_pair : graph) {
        Node* node = node_pair.second;

        if (cs_set.count(node_pair.first)) {
            for (Edge* edge : node->getEdges()) {
                pipes_to_remove.insert(edge->getPipe()->getId());
            }
            for (const auto& parent_pair : node->getParents()) {
                pipes_to_remove.insert(parent_pair.second->getPipe()->getId());
            };
        };
    };

    std::vector<int> edges_ids(pipes_to_remove.begin(), pipes_to_remove.end());

    RemoveEdge(graph, edges_ids);

    for (int cs_id : cs_set) {
        auto it = graph.find(cs_id);
        if (it != graph.end()) {
            delete it->second;
            graph.erase(it);
        };
    };
};
