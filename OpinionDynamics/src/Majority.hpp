//
//  Majority.hpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/08/03.
//

#ifndef Majority_hpp
#define Majority_hpp

#include <stdio.h>
#include "AbstractInteration.hpp"
#include "NetworkGenerator.hpp"
#include "Opinion_Agent.hpp"
#include <vector>

namespace fs = std::__fs::filesystem;

class MajorityRule : public Abstract_Interaction{
private:
    string FileName;
    ofstream fileStream;
    fs::path filePath;
    
    int debate_group;
    Network *network;
    vector<Agent> *nodeVec;
    vector<vector<int>> *adjMxt;
    int n_A{0},n_B{0};
    
public:
    MajorityRule(string __fileName,int __group);
    MajorityRule(Network& __network,string __fileName,int __group);
    
    void setNetwork(Network& __network) override;
    void run(int __time) override;
    double getOpinionAverage() override;
    pair<int, int> getRandomPair() override;
    
    void setFraction_A(double __fraction);
    void setDebateGroup(int __group);
};

#endif /* Majority_hpp */
