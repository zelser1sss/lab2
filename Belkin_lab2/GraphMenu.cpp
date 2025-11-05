#include "GraphMenu.h"
#include "MenuFunctions.h"
#include "Validation.h"
#include "Utils.h"
#include "Graph.h"

bool isPipeUsed(const std::unordered_map<int, Node*>& graph, int pipe_id)
{
    for (const auto& node_pair : graph) {
        Node* node = node_pair.second;

        for (const Edge* edge : node->getEdges()) {
            if (edge->getPipe()->getId() == pipe_id) {
                return true;
            };
        };

        for (const auto& parent_pair : node->getParents()) {
            const Edge* edge = parent_pair.second;
            if (edge->getPipe()->getId() == pipe_id) {
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
        if (node->getCS()->getId() == cs_id) {
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
    node->getEdges().push_back(edge);
    adjacentNode->getParents()[node] = edge;
};

int FoundDiameter(std::map<int, Pipe>& pipe_list, std::unordered_map<int, Node*>& graph)
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
        std::cout << "\nТрубы с таким диаметром не найдены!\n";
        std::cout << "Перейдем к созданию трубы...\n";
        AddPipe(pipe_list, input_diameter);
        found_id.push_back(pipe_list.rbegin()->first);
    };

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
        };
    } while (is_selected);

    return pipe_id;
};

void FoundType(std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph, int& cs_start, int& cs_end)
{

    bool is_selected = true;
    std::cout << "\nВведите ID КС от которой хотите провести трубу: ";
    do {
        cs_start = ProverkaNumber<int>();
        if (cs_list.find(cs_start) != cs_list.end()) {
            is_selected = false;
        }
        else {
            std::cout << "КС с ID " << cs_start << " не существует\nВведите существующий ID КС: ";
        };
    } while (is_selected);

    std::cout << "Тип выбранной станции: " << cs_list[cs_start].getType() << std::endl;

    std::vector<int> all_same_type;
    for (const auto& element : cs_list)
    {
        if (element.second.getType() == cs_list[cs_start].getType() && element.first != cs_start) {
            all_same_type.push_back(element.first);
        };
    };

    if (all_same_type.empty()) {
        std::cout << "\nКС с таким типом не найдены!\n";
        std::cout << "Перейдем к созданию КС...\n";
        AddCS(cs_list, cs_list[cs_start].getType());
        all_same_type.push_back(cs_list.rbegin()->first);
    };

    std::vector<int> found_id;
    if (graph.find(cs_start) != graph.end()) {
        Node* startNode = graph[cs_start];
        std::unordered_set<int> connected_cs;

        for (const Edge* edge : startNode->getEdges()) {
            connected_cs.insert(edge->getAdjacentNode()->getCS()->getId());
        };

        for (int cs_id : all_same_type) {
            if (connected_cs.find(cs_id) == connected_cs.end()) {
                found_id.push_back(cs_id);
            };
        };
    }
    else {
        found_id = all_same_type;
    };

    if (found_id.empty()) {
        std::cout << "\nНет доступных КС для соединения! Ко всем КС этого типа уже есть соединение из КС [ID:" << cs_start << "]\n";
        std::cout << "Перейдем к созданию новой КС...\n";
        AddCS(cs_list, cs_list[cs_start].getType());
        found_id.push_back(cs_list.rbegin()->first);
    };

    DisplayFound(cs_list, found_id, "КС");

    std::cout << "Введите ID КС к которой хотите провести трубу: ";
    is_selected = true;
    do {
        is_selected = true;
        cs_end = ProverkaNumber<int>();
        for (auto& found_pipe_id : found_id)
        {
            if (cs_end == found_pipe_id) {
                is_selected = false;
            };
        };
        if (is_selected) {
            std::cout << "Введите ID КС в списке найденных КС: ";
        }
    } while (is_selected);
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

bool hasCycleDFS(Node* node, std::unordered_set<Node*>& visited, std::unordered_set<Node*>& recursionStack)
{
    if (recursionStack.count(node)) {
        return true;
    }

    if (visited.count(node)) {
        return false;
    }

    visited.insert(node);
    recursionStack.insert(node);

    for (Edge* edge : node->getEdges()) {
        if (hasCycleDFS(edge->getAdjacentNode(), visited, recursionStack)) {
            return true;
        };
    };

    recursionStack.erase(node);
    return false;
}

bool isAcyclicGraph(std::unordered_map<int, Node*>& graph)
{

    std::unordered_set<Node*> visited;
    std::unordered_set<Node*> recursionStack;

    for (const auto& node_pair : graph) {
        Node* node = node_pair.second;

        if (!visited.count(node)) {
            if (hasCycleDFS(node, visited, recursionStack)) {
                return false;
            };
        };
    };

    return true;
};

std::vector<int> topologicalSort(std::unordered_map<int, Node*>& graph)
{
    std::vector<int> result;

    std::unordered_map<Node*, int> inDegree;
    for (const auto& node_pair : graph) {
        inDegree[node_pair.second] = 0;
    };

    for (const auto& node_pair : graph) {
        Node* node = node_pair.second;
        for (Edge* edge : node->getEdges()) {
            inDegree[edge->getAdjacentNode()]++;
        };
    };

    std::unordered_set<Node*> zeroInDegree;
    for (const auto& pair : inDegree) {
        if (pair.second == 0) {
            zeroInDegree.insert(pair.first);
        };
    };

    while (!zeroInDegree.empty()) {
        auto it = zeroInDegree.begin();
        Node* node = *it;
        zeroInDegree.erase(it);

        result.push_back(node->getId());

        for (Edge* edge : node->getEdges()) {
            Node* adjacent = edge->getAdjacentNode();
            inDegree[adjacent]--;
            if (inDegree[adjacent] == 0) {
                zeroInDegree.insert(adjacent);
            };
        };
    };

    return result;
};

void initHashTables(Node* start, std::unordered_map<int, Node*>& graph, std::unordered_set<Node*>& unprocessedNodes, std::unordered_map<Node*, float>& lengthToNodes)
{
    for (const auto& node_pair : graph) {
        Node* node = node_pair.second;
        unprocessedNodes.insert(node);
        lengthToNodes[node] = std::numeric_limits<float>::infinity();
    };
    lengthToNodes[start] = 0;
};

Node* getNodeWithMinLengthTolt(std::unordered_set<Node*>& unprocessedNodes, std::unordered_map<Node*, float>& lengthToNodes)
{
    Node* nodeWithMinLengthTolt = nullptr;
    float minLength = std::numeric_limits<float>::infinity();

    for (Node* node : unprocessedNodes) {
        float length = lengthToNodes[node];
        if (length < minLength) {
            minLength = length;
            nodeWithMinLengthTolt = node;
        };
    };
    return nodeWithMinLengthTolt;
};

void calculateLengthToEachNode(std::unordered_set<Node*>& unprocessedNodes, std::unordered_map<Node*, float>& lengthToNodes)
{
    while (!unprocessedNodes.empty()) {
        Node* node = getNodeWithMinLengthTolt(unprocessedNodes, lengthToNodes);
        if (node == nullptr) {
            auto it = unprocessedNodes.begin();
            unprocessedNodes.erase(it);
            continue;
        };
        if (lengthToNodes[node] == std::numeric_limits<float>::infinity()) return;
        for (Edge* edge : node->getEdges()) {
            Node* adjacentNode = edge->getAdjacentNode();
            if (unprocessedNodes.count(adjacentNode)) {
                float lengthToCheck = lengthToNodes[node] + edge->getLength();
                if (lengthToCheck < lengthToNodes[adjacentNode]) {
                    lengthToNodes[adjacentNode] = lengthToCheck;
                };
            };
        };
        unprocessedNodes.erase(node);
    };
};

std::vector<Node*> getShortestPath(Node* start, Node* end, std::unordered_map<Node*, float>& lengthToNodes)
{
    std::vector<Node*> path;
    Node* node = end;
    while (node != start) {
        float minLengthToNode = lengthToNodes[node];
        path.insert(path.begin(), node);
        for (const auto& node_pair : node->getParents()) {
            Node* parent = node_pair.first;
            Edge* parentEdge = node_pair.second;
            if (lengthToNodes.find(parent) == lengthToNodes.end()) continue;
            bool prevNodeFound = (parentEdge->getLength() + lengthToNodes[parent]) == minLengthToNode;
            if (prevNodeFound) {
                lengthToNodes.erase(node);
                node = parent;
                break;
            };
        };
    };
    path.insert(path.begin(), node);
    return path;
};

std::vector<Node*> getShortestPath(std::unordered_map<int, Node*>& graph, Node* start, Node* end)
{
    std::unordered_set<Node*> unprocessedNodes;
    std::unordered_map<Node*, float> lengthToNodes;

    initHashTables(start, graph, unprocessedNodes, lengthToNodes);
    calculateLengthToEachNode(unprocessedNodes, lengthToNodes);
    if (lengthToNodes[end] == std::numeric_limits<float>::infinity()) {
        return std::vector<Node*>();
    };
    return getShortestPath(start, end, lengthToNodes);
};

void FunctionToCreateGraph(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph)
{
    std::vector<int> selected_data;

    if (pipe_list.size() < 1 || cs_list.size() < 2)
    {
        std::cout << "\nСлишком мало труб и кс для создания графа\n";
        return;
    };

    int pipe_id = FoundDiameter(pipe_list, graph);

    int cs_start;
    int cs_end;

    FoundType(cs_list, graph, cs_start, cs_end);
    
    selected_data.push_back(cs_start);
    selected_data.push_back(cs_end);
    selected_data.push_back(pipe_id);

    CreateGraph(pipe_list, cs_list, graph, selected_data);

    std::cout << "\nГраф добавлен: " << "CS [ID:" << cs_start << "] ----- (Pipe [ID:" << pipe_id << "]) -----> CS [ID:" << cs_end << "]\n";
    Logger::logAction("Создано соединение в графе: CS " + std::to_string(cs_start) + " -> CS " + std::to_string(cs_end) + " через трубу " + std::to_string(pipe_id));
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
    Logger::logAction("Удалена труба из графа", pipe_id);
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
    Logger::logAction("Удалена КС из графа", cs_id);
};

void FunctionToTopologicalSort(std::unordered_map<int, Node*>& graph)
{

    if (graph.empty()) {
        std::cout << "\nГраф пуст!\n";
        Logger::logError("Пустой граф");
        return;
    };

    if (!isAcyclicGraph(graph)) {
        std::cout << "\nОшибка: Граф содержит циклы, топологическая сортировка невозможна!\n";
        Logger::logError("Граф циклический. Топологическая сортировка невозможна");
        return;
    };

    std::vector<int> sorted = topologicalSort(graph);

    std::cout << "\nТопологическая сортировка:\n";
    for (size_t i = 0; i < sorted.size(); ++i) {
        std::cout << i+1 << ". КС[ID:" << sorted[i] << "]\n";
    };
    Logger::logAction("Выполнена топологическая сортировка графа");
};

void DisplayGraph(const std::unordered_map<int, Node*>& graph)
{
    if (graph.empty()) {
        std::cout << "\nГраф пуст!\n";
        return;
    }

    std::cout << "\n--------------------------------------\n";
    std::cout << "         СТРУКТУРА ГРАФА\n";
    std::cout << "--------------------------------------\n";

    for (const auto& node_pair : graph) {
        Node* node = node_pair.second;

        std::cout << "КС[ID:" << node->getId() << "]";

        if (node->getEdges().empty()) {
            std::cout << " ---> (нет исходящих труб)";
        }
        else {
            std::cout << " ---> ";
            for (size_t i = 0; i < node->getEdges().size(); ++i) {
                const Edge* edge = node->getEdges()[i];
                std::cout << "КС[ID:" << edge->getAdjacentNode()->getId() << "]";
                std::cout << "(Труба[ID:" << edge->getPipe()->getId() << "])";

                if (i < node->getEdges().size() - 1) {
                    std::cout << ", ";
                };
            };
        };
        std::cout << "\n";
    };
    Logger::log("Отображена структура графа");
};

void FunctionToFindShortPath(std::unordered_map<int, Node*>& graph)
{
    if (graph.size() < 2)
    {
        std::cout << "\nНедостаточно КС в графе!\n";
        Logger::logError("Недостаточно КС для поиска кратчайшего пути");
        return;
    };

    int start;
    int end;
    bool is_selected = true;
    std::cout << "\nВведите ID КС начала пути: ";
    do {
        start = ProverkaNumber<int>();
        if (isCSUsed(graph, start)) {
            do {
                std::cout << "Введите ID КС конец пути: ";
                end = ProverkaNumber<int>();
                if (isCSUsed(graph, end) && start != end) {
                    is_selected = false;
                }
                else {
                    if (start == end) {
                        std::cout << "КС начала не может быть концом!\nВведите другое КС: ";
                    }
                    else {
                        std::cout << "КС с таким ID не используется в графе\nВведите КС, используемое в графе: ";
                    };
                };
            } while (is_selected);
        }
        else {
            std::cout << "КС с таким ID не используется в графе\nВведите КС, используемое в графе: ";
        };
    } while (is_selected);

    std::vector<Node*> shortPath = getShortestPath(graph, graph[start], graph[end]);

    if (shortPath.empty()) {
        std::cout << "\nНет пути между задаными КС\n";
        Logger::log("Поиск кратчайшего пути: путь не найден между КС " + std::to_string(start) + " и " + std::to_string(end));
        return;
    };

    std::cout << "\nКратчайший путь от КС[ID:" << start << "] до КС[ID:" << end << "]:\n";
    for (size_t i = 0; i < shortPath.size(); ++i) {
        std::cout << "КС[ID:" << shortPath[i]->getId() << "]";
        if (i < shortPath.size() - 1) {
            std::cout << " ---> ";
        };
    };
    std::cout << "\n";
    Logger::logAction("Найден кратчайший путь между КС " + std::to_string(start) + " и " + std::to_string(end));
};

void GraphMenu(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph)
{
    Logger::log("Вход в меню графов");
    while (1) {
        std::cout << "\n--------------------------------------\n";
        std::cout << "Выберите опцию:\n1. Добавить соединение КС\n2. Удалить трубу из графа\n3. Удалить КС из графа\n4. Показать граф\n5. Топологическая сортировка\n6. Найти крайтчайший путь между КС\n9. Вернутся в главное меню\n";
        std::cout << "--------------------------------------\n\n";
        int option;
        option = ProverkaNumber<int>();

        switch (option) {
        case 1:
            Logger::log("Выбрана опция: Добавить соединение КС");
            FunctionToCreateGraph(pipe_list,cs_list, graph);
            break;
        case 2:
            Logger::log("Выбрана опция: Удалить трубу из графа");
            FunctionToRemoveEdge(graph);
            break;
        case 3:
            Logger::log("Выбрана опция: Удалить КС из графа");
            FunctionToRemoveNode(graph);
            break;
        case 4:
            Logger::log("Выбрана опция: Показать граф");
            DisplayGraph(graph);
            break;
        case 5:
            Logger::log("Выбрана опция: Топологическая сортировка");
            FunctionToTopologicalSort(graph);
            break;
        case 6:
            Logger::log("Выбрана опция: Найти кратчайший путь между КС");
            FunctionToFindShortPath(graph);
            break;
        case 9:
            std::cout << "\nВыходим из меню графов\n\n";
            Logger::log("Выход из меню графов");
            return;
        default:
            std::cout << "Неизвестная опция. Попробуйте еще раз\n\n";
            Logger::log("Выбрана неизвестная опция в меню графов: " + std::to_string(option));
            break;
        };
    };
};