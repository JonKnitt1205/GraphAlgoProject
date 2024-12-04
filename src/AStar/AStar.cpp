#include "AStar.hpp"

#include <iostream>

bool AStar::oneIteration(uint32_t destNode, std::priority_queue<uint32_t, std::vector<uint32_t>, Compare>& openSet, const Graph::AdjList& adjList, 
std::unordered_map<uint32_t, double>& gScores, std::unordered_map<uint32_t, double>& fScores, std::vector<size_t>& parents, const Graph::PosList& positions) 
{
    uint32_t current = openSet.top();
    openSet.pop();
    if (current == destNode) { return true; }

    for (const Graph::Edge& neighbor : adjList.at(current)) {
        uint32_t neighborNode = neighbor.dest;
        double currgScore = gScores.at(current) + neighbor.cost;

        if (currgScore < gScores.at(neighborNode)) {
            parents.at(neighborNode) = current;
            gScores.at(neighborNode) = currgScore;
            fScores.at(neighborNode) = gScores.at(neighborNode) + getHeuristic(neighborNode, destNode, positions);

            openSet.push(neighborNode);
        }
    }
    return false;
}

void AStar::initScores(std::unordered_map<uint32_t, double> &gScores, std::unordered_map<uint32_t, double> &fScores, const Graph::PosList &positions)
{
    for (size_t i = 0; i < positions.size(); i++) {
        gScores[i] = Graph::INFDISTANCE;
        fScores[i] = Graph::INFDISTANCE;
    }
}

double AStar::getHeuristic(uint32_t curr, uint32_t dest, const Graph::PosList &positions)
{
    uint32_t x1 = positions.at(curr).first;
    uint32_t y1 = positions.at(curr).second;
    uint32_t x2 = positions.at(dest).first;
    uint32_t y2 = positions.at(dest).second;
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

void AStar::initParents(std::vector<size_t>& parents, uint32_t size) {
    parents.clear();
    parents.resize(size);
    for(uint32_t i = 0; i < size; i++) { parents.at(i) = i; }
}

void AStar::getPath(const Graph::AdjList& adjList, const Graph::PosList& positions, std::vector<double>& distance, std::vector<size_t>& parents, uint32_t destNode) {
    std::unordered_map<uint32_t, double> fScores;
    std::unordered_map<uint32_t, double> gScores;
    initScores(gScores, fScores, positions);
    initParents(parents, adjList.size());

    gScores.at(0) = 0;
    fScores.at(0) = getHeuristic(0, destNode, positions);

    Compare compare(fScores); 
    std::priority_queue<uint32_t, std::vector<uint32_t>, Compare> openSet(compare);
    openSet.push(0);

    while (!openSet.empty()) {
        if(oneIteration(destNode, openSet, adjList, gScores, fScores, parents, positions)) {
            return;
        } 
    }
}
