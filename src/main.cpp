#include "CaseCreator.hpp"
#include "CaseParser.hpp"

void createCase() {
    CaseCreator creator;
    creator.createTestCase(10, 2, 123456789, "Output/test.txt");
}

void printAllEdges(const std::vector<std::vector<GraphEdge>>& adjList) {
    for(size_t i = 0; i < adjList.size(); i++) {
        for(const GraphEdge& edge : adjList.at(i)) {
            std::cout << i << " - " << edge.cost << " -> " << edge.dest << std::endl;
        }
    }
}

int main() {
    createCase();
    CaseParser parser;
    bool randomDistances = true;
    parser.parseCase("Output/test.txt", randomDistances);

    const std::vector<std::vector<GraphEdge>>& adjList = parser.getAdjList();
    
    // print all edges just to prove it all worked lol
    printAllEdges(adjList);

    // here you would call the algos
}