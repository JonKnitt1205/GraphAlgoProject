#pragma once

#include <vector>

namespace Graph {
    typedef struct {
        size_t dest;
        double cost;
    } Edge;

    typedef std::vector<Edge> EdgeList;
    typedef std::vector<EdgeList> AdjList;

    const double INFDISTANCE = std::numeric_limits<double>::max();
};


