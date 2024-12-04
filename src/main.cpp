#include "CaseParser.hpp"
#include "BellmanFord.hpp"
#include "AStar.hpp"
#include "FunctionTimer.hpp"
#include <stack>
#include <iostream>

void printPath(const std::vector<size_t> parents, uint32_t dest) {
    uint32_t curNode = dest;
    std::stack<uint32_t> path;
    path.push(curNode);
    while(curNode != 0) {
        curNode = parents.at(curNode);
        path.push(curNode);
    }

    std::cout << path.top();
    path.pop();
    while(!path.empty()) {
        std::cout << "->" << path.top();
        path.pop();
    }
    std::cout << std::endl;
}

void testBF(const Graph::AdjList& adjlist, uint32_t dest) {
    std::vector<double> distResult;
    std::vector<size_t> parentResult;
    BellmanFord::runBellmanFord(adjlist, distResult, parentResult);
    printPath(parentResult, dest);
}

void testAStar(const Graph::AdjList& adjlist, const Graph::PosList& positions, uint32_t dest) {
    std::vector<double> distResult;
    std::vector<size_t> parentResult;
    AStar::getPath(adjlist, positions, distResult, parentResult, dest);
    printPath(parentResult, dest);
}

int main() {
    CaseParser parser;
    parser.parseCase("TestCases/largeSparse.txt");
    std::cout << "parsed the test case" << std::endl;
    const Graph::AdjList& adjlist = parser.getAdjList();
    const Graph::PosList& positions = parser.getPositions();

    srand(time(0));
    uint32_t destination = rand() % (adjlist.size() - 1) + 1;

    double Atime = timer(&testAStar, adjlist, positions, destination);
    double bftime = timer(&testBF, adjlist, destination);

    std::cout << "ATime: " << Atime << "ms" << std::endl;
    std::cout << "BFTime: " << bftime << "ms" << std::endl;
}