#include "GraphMenu.h"
#include "MenuFunctions.h"
#include "Validation.h"
#include "Utils.h"
#include "Graph.h"
#include "GraphAlgorithms.h"
#include "GraphOperations.h"

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

void FunctionToRemoveEdge(std::unordered_map<int, Node*>& graph, std::map<int, Pipe>& pipe_list)
{
    std::cout << "\nВведите ID трубы, которую хотите удалить из графа: ";
    int pipe_id = isReal(pipe_list, "Труба");

    if (!isUsedInGraph(graph, pipe_id, "Pipe")) {
        std::cout << "Труба не используется в графе!\n";
        return;
    };

    std::vector<int> pipe_ids;
    pipe_ids.push_back(pipe_id);
    RemoveEdge(graph, pipe_ids);

    std::cout << "\nТруба [ID:" << pipe_id << "] удалена из графа\n";
    Logger::logAction("Удалена труба из графа", pipe_id);
};

void FunctionToRemoveNode(std::unordered_map<int, Node*>& graph, std::map<int, CS>& cs_list)
{
    std::cout << "\nВведите ID КС, которую хотите удалить из графа: ";
    int cs_id = isReal(cs_list, "КС");

    if (!isUsedInGraph(graph, cs_id, "CS")) {
        std::cout << "КС не используется в графе!\n";
        return;
    };

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
        std::cout << i + 1 << ". КС[ID:" << sorted[i] << "]\n";
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

void FunctionToFindShortPath(std::unordered_map<int, Node*>& graph, std::map<int, CS>& cs_list)
{
    if (graph.size() < 2)
    {
        std::cout << "\nНедостаточно КС в графе!\n";
        Logger::logError("Недостаточно КС для поиска кратчайшего пути");
        return;
    };

    int start, end;

    std::cout << "\nВведите ID КС начала пути: ";
    start = isReal(cs_list, "КС");

    if (!isUsedInGraph(graph, start, "CS")) {
        std::cout << "КС не используется в графе!\n";
        return;
    }

    std::cout << "Введите ID КС конца пути: ";
    end = isReal(cs_list, "КС");

    if (!isUsedInGraph(graph, end, "CS")) {
        std::cout << "КС не используется в графе!\n";
        return;
    }

    if (start == end) {
        std::cout << "КС начала не может быть концом!\n";
        return;
    }

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

void FunctionToFindMaxFlow(std::unordered_map<int, Node*>& graph, std::map<int, CS>& cs_list)
{
    if (graph.size() < 2) {
        std::cout << "\nНедостаточно КС в графе!\n";
        Logger::logError("Недостаточно КС для поиска максимального потока");
        return;
    }

    int source_id, sink_id;

    std::cout << "\nВведите ID КС-источника: ";
    source_id = isReal(cs_list, "КС");

    if (!isUsedInGraph(graph, source_id, "CS")) {
        std::cout << "КС не используется в графе!\n";
        return;
    }

    std::cout << "Введите ID КС-стока: ";
    sink_id = isReal(cs_list, "КС");

    if (!isUsedInGraph(graph, sink_id, "CS")) {
        std::cout << "КС не используется в графе!\n";
        return;
    }

    if (source_id == sink_id) {
        std::cout << "Источник не может быть стоком!\n";
        return;
    }

    int maxFlow = ford_fulkerson(graph, source_id, sink_id);

    std::cout << "\nМаксимальный поток от КС[ID:" << source_id << "] до КС[ID:" << sink_id << "]: " << maxFlow << "\n";
    Logger::logAction("Найден максимальный поток: " + std::to_string(maxFlow) +
        " между КС " + std::to_string(source_id) + " и " + std::to_string(sink_id));
};

void GraphMenu(std::map<int, Pipe>& pipe_list, std::map<int, CS>& cs_list, std::unordered_map<int, Node*>& graph)
{
    Logger::log("Вход в меню графов");
    while (1) {
        std::cout << "\n--------------------------------------\n";
        std::cout << "Выберите опцию:\n1. Добавить соединение КС\n2. Удалить трубу из графа\n3. Удалить КС из графа\n4. Показать граф\n5. Топологическая сортировка\n6. Найти крайтчайший путь между КС\n7. Найти максимальный поток\n9. Вернутся в главное меню\n";
        std::cout << "--------------------------------------\n\n";
        int option;
        option = ProverkaNumber<int>();

        switch (option) {
        case 1:
            Logger::log("Выбрана опция: Добавить соединение КС");
            FunctionToCreateGraph(pipe_list, cs_list, graph);
            break;
        case 2:
            Logger::log("Выбрана опция: Удалить трубу из графа");
            FunctionToRemoveEdge(graph, pipe_list);
            break;
        case 3:
            Logger::log("Выбрана опция: Удалить КС из графа");
            FunctionToRemoveNode(graph, cs_list);
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
            FunctionToFindShortPath(graph, cs_list);
            break;
        case 7:
            Logger::log("Выбрана опция: Найти максимальный поток");
            FunctionToFindMaxFlow(graph, cs_list);
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