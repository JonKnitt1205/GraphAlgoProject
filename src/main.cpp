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

void printAllPositions(const std::vector<std::pair<uint32_t, uint32_t>>& positions) {
    for(size_t i = 0; i < positions.size(); i++) {
        std::cout << "Node " << i << " is at (" << positions.at(i).first;
        std::cout << ", "  << positions.at(i).second << ")" << std::endl;
    }
}

int main() {
    createCase();
    CaseParser parser;
    bool randomDistances = true;
    parser.parseCase("Output/test.txt", randomDistances);

    const std::vector<std::vector<GraphEdge>>& adjList = parser.getAdjList();
    const std::vector<std::pair<uint32_t, uint32_t>>& positions = parser.getPositions();
    
    // print all edges just to prove it all worked lol
    printAllEdges(adjList);
    printAllPositions(positions);

    // here you would call the algos
}