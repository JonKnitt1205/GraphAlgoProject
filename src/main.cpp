#include "CaseCreator.hpp"
#include "CaseParser.hpp"
#include "BellmanFord.hpp"

void createCase() {
    CaseCreator creator;
    creator.createTestCase(10, 2, 123456789, "Output/test.txt");
}

void printAllEdges(const Graph::AdjList& adjList) {
    for(size_t i = 0; i < adjList.size(); i++) {
        for(const Graph::Edge& edge : adjList.at(i)) {
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

void testBF(const Graph::AdjList& adjlist) {
    std::vector<double> distResult;
    std::vector<size_t> parentResult;
    
    if(!BellmanFord::runBellmanFord(adjlist, distResult, parentResult)) { 
        std::cout << "Bellman Ford Failed: Graph contains a negative cycle" << std::endl; 
        return;
    }
    
    std::cout << "Bellman Ford Completed With Final Disatances: ";
    for(const double d : distResult) {
        std::cout << d << ' ';
    }
    std::cout << std::endl;
}

int main() {
    // createCase();
    // CaseParser parser;
    // bool randomDistances = true;
    // parser.parseCase("Output/test.txt", randomDistances);

    // const Graph::AdjList& adjList = parser.getAdjList();
    // const std::vector<std::pair<uint32_t, uint32_t>>& positions = parser.getPositions();
    
    // // print all edges just to prove it all worked lol
    // printAllEdges(adjList);
    // printAllPositions(positions);

    const Graph::AdjList& adjlistGood = {
        {{1, 5}}, // 0-(5)->1
        {{2, 1}, {3, 2}}, // 1-(1)->2 1-(2)->3
        {{4, 1}}, // 1-(1)->4
        {}, 
        {{3, -1}} // 4-(-1)->3
    };
    testBF(adjlistGood);

    const Graph::AdjList& adjlistBad = {
        {{1, 4}}, // 0-(4)->1
        {{2, -6}}, // 1-(-6)->2
        {{3, 5}}, // 2-(5)->3
        {{1, -2}}, // 3-(-2)->1
    };
    testBF(adjlistBad);

}