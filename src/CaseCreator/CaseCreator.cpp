#include "CaseCreator.hpp"

CaseCreator::CaseCreator(){
    m_adjlist_p = new std::vector<std::unordered_set<uint32_t>>;
    m_coords_p = new std::vector<std::pair<uint32_t, uint32_t>>;
}


CaseCreator::~CaseCreator() {
    delete m_adjlist_p;
    delete m_coords_p;
}

void CaseCreator::createTestCase(uint32_t nodeCount, uint32_t suggestedMaxOutgoing, uint32_t randomSeed,  const std::string &outputFileName)
{
    init(nodeCount, suggestedMaxOutgoing, randomSeed);
    resetAndResizeData();
    initAllNodes();
    // std::cout << "created nodes now making graph traversable from any start node" << std::endl;
    // for(uint32_t n = 0; n < m_nodeCount; n++) { makeCaseConnected(n); }
    makeCaseConnected(0);
    putCaseIntoFile(outputFileName);
}

void CaseCreator::init(uint32_t nodeCount, uint32_t suggestedMaxOutgoing, uint32_t randomSeed) {
    m_nodeCount = nodeCount;
    m_suggestedMaxOutgoing = suggestedMaxOutgoing;
    srand(randomSeed);
}

void CaseCreator::resetAndResizeData() {
    m_adjlist_p->clear();
    m_adjlist_p->resize(m_nodeCount);
    m_coords_p->clear();
    m_coords_p->resize(m_nodeCount);
}

void CaseCreator::initAllNodes() {
    for(uint32_t curNode = 0; curNode < m_nodeCount; curNode++) { 
        initializeNodeRandomly(curNode); 
    }
}

void CaseCreator::initializeNodeRandomly(uint32_t node) {
    setRandomPosition(node);
    setRandomNeighbors(node);
    // std::cout << "created node " << node << "/ " << m_nodeCount << std::endl;
}

void CaseCreator::setRandomPosition(uint32_t node) {
    uint32_t x = rand() % m_nodeCount;
    uint32_t y = rand() % m_nodeCount;
    m_coords_p->at(node) = {x, y};
}

void CaseCreator::setRandomNeighbors(uint32_t node) {
    // a node can be adjacent to 1 to nodeCount - 1 other nodes (not adjacent to self)
    uint32_t numberOfOutgoingEdges = rand() % m_suggestedMaxOutgoing + 1;
    std::unordered_set<uint32_t>& neighborNodes = m_adjlist_p->at(node);
    neighborNodes.clear();
    for(uint32_t i = 0; i < numberOfOutgoingEdges; i++) {
        uint32_t neighbor;
        do {
            neighbor = rand() % m_nodeCount;
        } while(neighborNodes.count(neighbor) || neighbor == node);
        neighborNodes.insert(neighbor);
    }
}

void CaseCreator::makeCaseConnected(uint32_t node) {
    std::unordered_set<u_int32_t>* unseen_p = new std::unordered_set<u_int32_t>;
    for(uint32_t n = 0; n < m_nodeCount; n++) { unseen_p->insert(n); }

    // bfs
    std::queue<uint32_t>* q_p = new std::queue<uint32_t>;
    BFS(q_p, unseen_p, node);

    // give the unseen nodes seen parents
    while(!unseen_p->empty()) {
        auto it = unseen_p->begin();
        uint32_t source;
        do {
            source = rand() % m_nodeCount;
        // make sure randomly chosen node is not unseen and is not itself
        } while(unseen_p->count(source) || source == *it);
        m_adjlist_p->at(source).insert(*it);
        BFS(q_p, unseen_p, *it);
    }

    delete unseen_p;
    delete q_p;
}

void CaseCreator::putCaseIntoFile(const std::string& filename) {
    std::ofstream output(filename);
    for(uint32_t curNode = 0; curNode < m_nodeCount; curNode++) {
        output << curNode << ' ' << m_coords_p->at(curNode).first << ' ' << m_coords_p->at(curNode).second;
        for(uint32_t neighbor : m_adjlist_p->at(curNode)) {
            output << ' ' << neighbor;
        }
        output << std::endl;
    }
}

void CaseCreator::BFS(std::queue<uint32_t>* q_p, std::unordered_set<u_int32_t>* unseen_p, uint32_t node) {
    q_p->push(node);
    while(!q_p->empty()) {
        uint32_t n = q_p->front();
        q_p->pop();
        if(!unseen_p->count(n)) { continue; }
        unseen_p->erase(n);
        for(uint32_t next : m_adjlist_p->at(n)) {
            q_p->push(next);
        }
    }
}