//
//  NetworkGenerator.hpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/07/26.
//

#ifndef NetworkGenerator_hpp
#define NetworkGenerator_hpp

#include "NetworkMethod.hpp"
#include "Opinion_Agent.hpp"
#include "NetworkEdge.hpp"
#include <stdio.h>
#include <vector>
#include <fstream>

using namespace std;



class Network : public NetworkMethod{
private:
    //variables
    bool isWeight;
    bool isAlltoALL;
    int totalEdges,totalNodes,totalDegree;
    vector<vector<int>> adjMtx;
    vector<Agent> nodeVec;
    vector<Edge> edgeVec;
    int n_A{0}, n_B{0};
    
    //functions
    void addNode(int index) override;
    void addEdge(int first, int second) override;
    pair<int, int> randomPair();
    
    
public:
    
    // constructor and generator for network
    Network();
    Network(bool isWeight,int totalNode,int totalEdge = 0);
    Network(bool isWeight,int totalNode,double prob);
    void generate();
    void generate(double __p);
    
    //functions
    int getTotalNumberofEdge() override;
    int getTotalNumberofNode() override;
    int getTotalNumberofDegree() override;
    void printAdjacency() override;
    void printAllEdge() override;
    void printAllNode() override;
    
    void setFullConnected(bool __bool);
    bool isFullConnected();
    
    void setOpinionToAgents();
    void setContinueousOpinionToAgents();
    
    void resetOpinions();
    void setFractionA(double __fraction_A);
    void doVoterRule();
    void doMajorityRule(int __group);
    void doDeffuantRule(double __mu , double __epsilon);
    
    int getNumberOfA();
    int getNumberOfB();
    vector<Agent>& getNodeVector();
    vector<vector<int>>& getAdjMtx();
    
    void resultFileOutput(ofstream& __outputStream);
    
    
};




#endif /* NetworkGenerator_hpp */
