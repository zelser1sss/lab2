#include "GraphAlgorithms.h"
#include <limits>

bool hasCycleDFS(Node* node, std::unordered_set<Node*>& visited, std::unordered_set<Node*>& recursionStack)
{
    if (recursionStack.count(node)) {
        return true;
    };

    if (visited.count(node)) {
        return false;
    };

    visited.insert(node);
    recursionStack.insert(node);

    for (Edge* edge : node->getEdges()) {
        if (hasCycleDFS(edge->getAdjacentNode(), visited, recursionStack)) {
            return true;
        };
    };

    recursionStack.erase(node);
    return false;
};

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

bool dfs(std::unordered_map<int, Node*>& graph, int src, int dst, std::list<Edge*>& path, std::unordered_set<int>& visited)
{
    if (src == dst) {
        return true;
    };

    if (visited.count(src)) {
        return false;
    };

    visited.insert(src);

    auto& adjacent = graph[src]->getEdges();
    for (auto edge : adjacent) {
        if (edge->residual_flow() <= 0) {
            continue;
        };

        if (dfs(graph, edge->getAdjacentNode()->getId(), dst, path, visited)) {
            path.push_front(edge);
            return true;
        };
    };

    return false;
};

int find_min_flow(const std::list<Edge*>& path)
{
    int min_flow = std::numeric_limits<int>::max();
    for (auto edge : path) {
        min_flow = std::min(min_flow, edge->residual_flow());
    };
    return min_flow;
};

int ford_fulkerson(std::unordered_map<int, Node*>& graph, int src, int dst)
{
    int max_flow = 0;

    for (auto& node_pair : graph) {
        for (auto edge : node_pair.second->getEdges()) {
            edge->setFlow(0);
        };
    };

    while (true) {
        std::list<Edge*> path;
        std::unordered_set<int> visited;

        if (!dfs(graph, src, dst, path, visited)) {
            break;
        };

        int min_flow = find_min_flow(path);

        for (auto edge : path) {
            edge->setFlow(edge->getFlow() + min_flow);
        };

        max_flow += min_flow;
    };

    return max_flow;
};