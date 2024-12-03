#pragma once

#include <fstream>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <queue>

class CaseCreator {
public:
    CaseCreator();
    ~CaseCreator();

    // creates a random fully connected graph in a coordiante space
    // output is formated as NODEINDEX XCOORD YCOORD ADJACENTNODE ADJACENTNODE ADJACENTNODE ...
    void createTestCase(uint32_t nodeCount, uint32_t suggestedMaxOutgoing, uint32_t randomSeed, const std::string& outputFileName);

private:
    // set the node count and random seed
    void init(uint32_t nodeCount, uint32_t randomSeed, uint32_t suggestedMaxOutgoing);

    // inititalize nodeCounts nodes randomly
    void initAllNodes();

    // gives node random position and random outgoing edges
    void initializeNodeRandomly(uint32_t node);

    // sets a random position for the given node to be in the grid of nodecount x nodecount
    void setRandomPosition(uint32_t node);

    // gives a random number of random outgoing edges to this node
    void setRandomNeighbors(uint32_t node);

    // clears all of the data structure when a new test case is requested
    void resetAndResizeData();

    // modifies the current case and makes it connected (so no sets are disjoint)
    // makes it so that all other nodes are reachable from given source node
    void makeCaseConnected(uint32_t node);

    // output is formated as NODEINDEX ADJACENTNODE ADJACENTNODE ADJACENTNODE ...
    void putCaseIntoFile(const std::string& filename);

    void BFS(std::queue<uint32_t>* q_p, std::unordered_set<u_int32_t>* unseen_p, uint32_t node);

    bool isValid();
private:
    std::vector<std::unordered_set<uint32_t>>* m_adjlist_p;
    std::vector<std::pair<uint32_t, uint32_t>>* m_coords_p;
    uint32_t m_suggestedMaxOutgoing = 0;
    uint32_t m_nodeCount = 0;
};
