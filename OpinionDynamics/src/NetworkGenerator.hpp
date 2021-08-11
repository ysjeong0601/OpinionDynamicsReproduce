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
    pair<int, int> selectNodePair();
    
    
public:
    
    // constructor and generator for network
    Network();
    Network(bool isWeight,int totalNode,int totalEdge = 0);
    Network(bool isWeight,int totalNode,double prob);
    void generate();
    void generate(double __p);
    void generate_Barabasi_Albert(int __init_deg, int __size);
    
    //functions
    int getTotalNumberofEdge() override;
    int getTotalNumberofNode() override;
    int getTotalNumberofDegree() override;
    void printAdjacency() override;
    void printAllEdge() override;
    void printAllNode() override;
    void fileOutput_Deg_dis(ofstream& __fileStream,string __fileName);
    
    void setFullConnected(bool __bool);
    bool isFullConnected();
    
    
    
    vector<Agent>& getNodeVector();
    vector<vector<int>>& getAdjMtx();
    
    virtual ~Network();
    
};




#endif /* NetworkGenerator_hpp */
