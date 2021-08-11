//
//  Voter.hpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/08/03.
//

#ifndef Voter_hpp
#define Voter_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "Opinion_Agent.hpp"
#include "AbstractInteration.hpp"
#include <filesystem>

namespace fs = std::__fs::filesystem;

class Voter : public Abstract_Interaction{
    
private:
    string FileName;
    ofstream fileStream;
    fs::path filePath;
    
    Network *network;
    vector<Agent> *nodeVec;
    vector<vector<int>> *adjMxt;
    int n_A{0},n_B{0};
    
public:
    
    Voter(string __fileName);
    Voter(Network& __network,string __fileName);
    
    void setNetwork(Network& __network) override;
    double getOpinionAverage() override;
    void run(int __time) override;
    pair<int, int> getRandomPair() override;
    
    void setFraction_A(double __fraction);
    
    virtual ~Voter();
};


#endif /* Voter_hpp */
