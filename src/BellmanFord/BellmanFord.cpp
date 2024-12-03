#include "BellmanFord.hpp"
 
bool BellmanFord::runBellmanFord(const Graph::AdjList& adjlist, std::vector<double>& distance, std::vector<size_t>& predecessor) {
    initLists(adjlist.size(), distance, predecessor);

    distance.at(0) = 0;
    for(size_t iteration = 0; iteration < adjlist.size(); iteration++) { 
        if(!relaxOnce(adjlist, distance, predecessor, iteration)) {
            return false;
        }
    }
    return true;
}

void BellmanFord::initLists(size_t nodeCount, std::vector<double>& distance, std::vector<size_t>& predecessor) {
    distance.clear();
    predecessor.clear();
    distance.resize(nodeCount, Graph::INFDISTANCE);
    predecessor.resize(nodeCount);
    for(size_t i = 0; i < nodeCount; i++) { predecessor.at(i) = i; }
}

bool BellmanFord::relaxOnce(const Graph::AdjList& adjlist, std::vector<double>& dist, std::vector<size_t>& pre, size_t iteration) {
    for(size_t u = 0; u < adjlist.size(); u++) {
        for(const Graph::Edge& e : adjlist.at(u)) {
            if(dist.at(u) == Graph::INFDISTANCE) { continue; }
            if(dist.at(u) + e.cost >= dist.at(e.dest)) { continue; }
            if(iteration == adjlist.size() - 1) { return false; }
            dist.at(e.dest) = dist.at(u) + e.cost;
            pre.at(e.dest) = u;
        }
    }
    return true;
}
