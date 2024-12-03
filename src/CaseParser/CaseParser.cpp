#include "CaseParser.hpp"

CaseParser::CaseParser() {
    m_adjlist_p = new AdjList;
    m_positions_p = new std::vector<std::pair<uint32_t, uint32_t>>;
}

CaseParser::~CaseParser() {
    delete m_adjlist_p;
    delete m_positions_p;
}

void CaseParser::parseCase(const std::string& inputFile, bool randomDistances) {
    m_adjlist_p->clear();
    
    loadPositions(inputFile);
    loadEdges(inputFile, randomDistances);
    
}

const std::vector<std::pair<uint32_t, uint32_t>>& CaseParser::getPositions() {
    return *m_positions_p;
}

const AdjList& CaseParser::getAdjList() {
    return *m_adjlist_p;
}

void CaseParser::loadPositions(const std::string& inputFile) {
    std::ifstream input(inputFile);
    std::string line;
    while(getline(input, line)) {
        uint32_t x, y;
        
        char* next;
        strtol(line.c_str(), &next, 10);
        x = strtol(next, &next, 10);
        y = strtol(next, &next, 10);

        m_positions_p->push_back({x, y});
    }
}

void CaseParser::loadEdges(const std::string& inputFile, bool randomDistances) {
    std::ifstream input(inputFile);
    std::string line;
    while(getline(input, line)) {
        EdgeList* e = new EdgeList;

        char* next;
        size_t node1 = strtol(line.c_str(), &next, 10);
        strtol(next, &next, 10);
        strtol(next, &next, 10);

        while(next[0] != '\0') {
            size_t node2 = strtol(next, &next, 10);
            double distance = getDistance(node1, node2);
            if(randomDistances) { distance = rand() % 1000 + 1; }

            e->push_back({node2, distance});
        }

        m_adjlist_p->push_back(*e);
        delete e;
    }
}

double CaseParser::getDistance(size_t node1, size_t node2) {
    uint32_t x1 = m_positions_p->at(node1).first;
    uint32_t y1 = m_positions_p->at(node1).second;
    uint32_t x2 = m_positions_p->at(node2).first;
    uint32_t y2 = m_positions_p->at(node2).second;

    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}
