//
//  Sznajd.hpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/08/06.
//

#ifndef Sznajd_hpp
#define Sznajd_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <filesystem>
#include "NetworkGenerator.hpp"

namespace fs = std::__fs::filesystem;

class Sznajd{
    
private:
    string FileName;
    ofstream fileStream;
    fs::path filePath;
    
    Network *network;
    vector<Agent> *nodeVec;
    vector<vector<int>> *adjMxt;
    int n_A{0},n_B{0};
    
public:
    Sznajd(Network& __network,string __fileName);
    Sznajd(string __fileName);
    void setNetwork(Network& __network);
    void setFraction_A(double __fraction);
    void run(int __time);
    double getOpinionAverage();
    
    virtual ~Sznajd();
};





#endif /* Sznajd_hpp */
