#include "CaseCreator.hpp"

int main(int argc, char* argv[]) {
    if(argc < 4) {
        std::cout << "Usage: CaseCreator <NODE_COUNT> <SUGGESTED_MAX_OUTGOING_EDGES_PER_NODE> <FILE_PATH> <RANDOM_SEED(optional)>" << std::endl;
        std::cout << "if no random seed is given, system time is used as the seed" << std::endl;
        exit(1);
    }
    
    uint32_t randomSeed = time(NULL);
    if(argc > 4) { randomSeed = std::strtoul(argv[4], nullptr, 10); }
    uint32_t nodeCount = std::strtoul(argv[1], nullptr, 10);
    uint32_t suggestedMaxOutgoing = std::strtoul(argv[2], nullptr, 10);
    std::string filepath =  argv[3];
    
    std::cout << "Creating test case of size " << nodeCount << " with suggested max out degree of " << suggestedMaxOutgoing; 
    std::cout <<  " with random seed " << randomSeed << std::endl;
    CaseCreator c;
    c.createTestCase(nodeCount, suggestedMaxOutgoing, randomSeed, filepath);
    std::cout << "Test case created at file location " << filepath << std::endl;
    std::cout << "Output format is NODE XPOS YPOS OUTGOING_DEST_1 OUTGOING_DEST_2 OUTGOING_DEST_3 ..." << std::endl; 
    std::cout << "Graph is traversable when starting node is set to be 0" << std::endl;
}