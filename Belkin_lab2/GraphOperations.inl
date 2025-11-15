#ifndef GRAPHOPERATIONS_INL
#define GRAPHOPERATIONS_INL


template <typename T>
int isReal(std::map<int, T>& container, std::string name)
{
    int id;
    bool is_selected = true;
    while (is_selected) {
        id = ProverkaNumber<int>();
        if (container.find(id) != container.end()) {
            return id;
        }
        else {
            std::cout << name << " с таким ID не существует!\n¬ведите ID существуещего объекта: ";
        };
    };
};

template <typename T>
int FoundObject(std::map<int, T>& container, std::unordered_map<int, Node*>& graph, int input, std::string name)
{
    std::vector<int> found_id;

    for (const auto& element : container) {
        if constexpr (std::is_same_v<T, Pipe>) {
            bool is_used = isUsedInGraph(graph, element.first, "Pipe");
            if (element.second.getDiameter() == input && is_used == false)
            {
                found_id.push_back(element.first);
            };
        }
        else if constexpr (std::is_same_v<T, CS>) {
            if (element.second.getType() == container[input].getType() && element.first != input) {
                int target_cs_id = element.first;
                bool has_connection = false;

                if (graph.find(input) != graph.end()) {
                    Node* startNode = graph[input];
                    for (const Edge* edge : startNode->getEdges()) {
                        if (edge->getAdjacentNode()->getId() == target_cs_id) {
                            has_connection = true;
                            break;
                        };
                    };
                };

                if (!has_connection && graph.find(target_cs_id) != graph.end()) {
                    Node* targetNode = graph[target_cs_id];
                    for (const Edge* edge : targetNode->getEdges()) {
                        if (edge->getAdjacentNode()->getId() == input) {
                            has_connection = true;
                            break;
                        };
                    };
                };

                if (!has_connection) {
                    found_id.push_back(target_cs_id);
                };
            };
        };
    };

    if (found_id.empty()) {
        std::cout << std::endl << name << " с заданными параметрами не найдено!\n";
        std::cout << "ѕерейдем к созданию нового объекта...\n";
        if constexpr (std::is_same_v<T, Pipe>) { AddPipe(container, input); }
        if constexpr (std::is_same_v<T, CS>) { AddCS(container, container[input].getType()); }
        found_id.push_back(container.rbegin()->first);
    };

    DisplayFound(container, found_id, name);

    std::cout << "¬ведите ID " << name << ": ";
    int object_id;
    bool is_selected;
    do {
        is_selected = true;
        object_id = ProverkaNumber<int>();
        for (auto& found_pipe_id : found_id)
        {
            if (object_id == found_pipe_id) {
                is_selected = false;
            };
        };
        if (is_selected) {
            std::cout << "¬ведите ID " << name << " в списке найденных: ";
        };
    } while (is_selected);

    return object_id;
};

#endif