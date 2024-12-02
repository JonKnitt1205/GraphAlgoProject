#pragma once

#include <vector>
#include <fstream>

typedef struct {
    size_t dest;
    double cost;
} GraphEdge;

typedef std::vector<GraphEdge> EdgeList;
typedef std::vector<EdgeList> AdjList;

class CaseParser {
public:
    CaseParser();
    ~CaseParser();
    
    // initializes the adj list
    void parseCase(const std::string& inputFile);

    const AdjList& getAdjList();
private:
    // load the positions from the file
    void loadPositions(const std::string& inputFile, std::vector<std::pair<uint32_t, uint32_t>>* positions_p);

    // using the loaded positions, load the edges into the adj list
    void loadEdges(const std::string& inputFile, std::vector<std::pair<uint32_t, uint32_t>>* positions_p);

    // find the distance between two nodes
    double getDistance(size_t node1, size_t node2, std::vector<std::pair<uint32_t, uint32_t>>* positions_p);

private:
    AdjList*  m_adjlist_p;
};
