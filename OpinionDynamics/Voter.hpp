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
#include <filesystem>

namespace fs = std::__fs::filesystem;

class Voter {
    
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
    void setNetwork(Network& __network);
    void run(int __time);
    void setFraction_A(double __fraction);
    double getOpinionAverage();
    
    
};


#endif /* Voter_hpp */
