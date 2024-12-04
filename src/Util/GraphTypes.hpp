#pragma once

#include <vector>

namespace Graph {
    typedef struct {
        size_t dest;
        double cost;
    } Edge;

    typedef std::vector<Edge> EdgeList;
    typedef std::vector<EdgeList> AdjList;
    typedef std::vector<std::pair<uint32_t, uint32_t>> PosList;

    const double INFDISTANCE = std::numeric_limits<double>::max();
};


