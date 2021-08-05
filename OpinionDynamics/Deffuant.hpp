//
//  Deffuant.hpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/08/01.
//

#ifndef Deffuant_hpp
#define Deffuant_hpp

#include <vector>
#include <string>
#include <filesystem>
#include <stdio.h>
#include "Opinion_Agent.hpp"

namespace fs = std::__fs::filesystem;

class Deffuant{
// use 'protected' for varibales because HK class inherits Deffuant
protected:
    string FileName;
    ofstream fileStream;
    fs::path filePath;
    
    double mu,epsilon;
    Network *network;
    vector<Agent> *nodeVec;
    vector<vector<int>> *adjMxt;
    
public:
    Deffuant(string __fileName,double __mu, double __epsilon);
    void setRandomOpinion();
    void setNetwork(Network& __network);
    void setParameter(double __mu, double __epsilon);
    void run(int __time);
    double getOpinionAverage();
};


#endif /* Deffuant_hpp */
