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
#include "AbstractInteration.hpp"

namespace fs = std::__fs::filesystem;

class Deffuant : public Abstract_Interaction{
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
    Deffuant(Network& __network, string __fileName,double __mu, double __epsilon);
    
    
    void setNetwork(Network& __network) override;
    void run(int __time) override;
    double getOpinionAverage() override;
    pair<int, int> getRandomPair() override;
    
    void setRandomOpinion();
    void setParameter(double __mu, double __epsilon);
};


#endif /* Deffuant_hpp */
