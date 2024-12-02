#include "CaseCreator.hpp"
#include "CaseParser.hpp"

void createCase() {
    CaseCreator creator;
    creator.createTestCase(10, 2, 123456789, "Output/test.txt");
}

int main() {
    createCase();
    CaseParser parser;
    parser.parseCase("Output/test.txt");

    const std::vector<std::vector<GraphEdge>>& adjList = parser.getAdjList();

    

    // here you would call the algos
}