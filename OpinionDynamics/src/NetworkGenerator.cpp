//
//  NetworkGenerator.cpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/07/26.
//

#include <vector>
#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#include <time.h>

#include "NetworkGenerator.hpp"

#define OPINION_A 1
#define OPINION_B -1
#define NULLOPINION 0


Network::Network(){
    
}

Network::Network(bool isWeight,int totalNode,int totalEdge){
    this->isWeight = isWeight;
    this->totalNodes = totalNode;
    this->totalEdges = totalEdge;
    this->isAlltoALL = false;
    generate();
}
Network::Network(bool isWeight, int totalNode,double prob){
    this->isWeight = isWeight;
    this->totalNodes = totalNode;
    this->totalEdges = 0;
    generate(prob);
}


void Network::generate(){
    int i,j;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0,totalNodes-1);
    
    // adjMtx
    for (i=0; i<totalNodes; i++) {
        vector<int> row;
        adjMtx.push_back(row);
    }
    
    // add nodes
    for (i=0; i<this->totalNodes; i++) {
        addNode(i);
    }
    // add edges
    for (i=0; i<this->totalEdges; i++) {
        int sNode1,sNode2;
        // check
        while(1){
            int check = 0;
            sNode1 = dis(gen);
            sNode2 = dis(gen);
            if (sNode1 == sNode2) {
                continue;
            }
            for (j=0; j<adjMtx[sNode1].size(); j++) {
                if(sNode2 ==adjMtx[sNode1][j]){ // already connected
                    check = 1;
                    break;
                }
            }
            if (check == 1) {
                continue;
            }else{
                break;
            }
        } // while-end
        
        // add edges;
        addEdge(sNode1, sNode2);
//        nodeVec[sEdge1].deg += 1;
//        nodeVec[sEdge2].deg += 1;
        nodeVec[sNode1].increaseDeg();
        nodeVec[sNode2].increaseDeg();
        
        adjMtx[sNode1].push_back(sNode2);
        adjMtx[sNode2].push_back(sNode1);
        
        
    }
}

void Network::generate(double __p){
    int i,j;
    srand((unsigned int)time(NULL));
    
    // adjMtx
    for (i=0; i<totalNodes; i++) {
        vector<int> row;
        adjMtx.push_back(row);
    }
    
    // add nodes
    for (i=0; i<this->totalNodes; i++) {
        addNode(i);
    }
    
    for (i=0; i<totalNodes; i++) {
        for (j=i; j<totalNodes; j++) {
            if (__p > (double)rand()/RAND_MAX) {
                // add edges;
                addEdge(i, j);
                nodeVec[i].increaseDeg();
                nodeVec[j].increaseDeg();
                
                adjMtx[i].push_back(j);
                adjMtx[j].push_back(i);
            }
        }
    }
    
}



//                                                              random pair 보류중
/*
pair<int, int> Network::randomPair(){
    int j;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0,totalNodes-1);
    int sNode1,sNode2;
    pair<int, int> random_pair;
    // check
    while(1){
        int check = 0;
        sNode1 = dis(gen);
        sNode2 = dis(gen);
        if (sNode1 == sNode2) {
            continue;
        }
        for (j=0; j<adjMtx[sNode1].size(); j++) {
            if(sNode2 ==adjMtx[sNode1][j]){ // already connected
                check = 1;
                break;
            }
        }
        if (check == 1) {
            continue;
        }else{
            break;
        }
    } // while-end
    random_pair.first = sNode1;
    random_pair.second = sNode2;
    
    return random_pair;
}
 */


void Network::setFullConnected(bool __bool){
    this->isAlltoALL = __bool;
}

bool Network::isFullConnected(){
    return this->isAlltoALL;
}

void Network::addNode(int index){
    Agent agent(index,NULLOPINION);
    this->nodeVec.push_back(agent);
}

void Network::addEdge(int first, int second){
    Edge edge(first,second);
    this->edgeVec.push_back(edge);
}


int Network::getTotalNumberofEdge(){
    return this->totalEdges;
}
int Network::getTotalNumberofNode(){
    return this->totalNodes;
}
int Network::getTotalNumberofDegree(){
    return this->totalDegree;
}

void Network::printAdjacency(){
    
}
void Network::printAllEdge(){
    for (Edge &edge : edgeVec) {
        cout << "edge " << "("<<edge.getNodePair().first<<","<<edge.getNodePair().second<< ")"  << "\n";
    }
}
void Network::printAllNode(){
    for (auto &node : nodeVec) {
        cout << "node "<< node.getIndex() << "(" << node.getDeg()<< ")" << " opi : ";
        switch (node.getOpinionState()) {
            case OPINION_A:
                cout << "(A,1)\n";
                break;
                
            case OPINION_B:
                cout << "(B,-1)\n";
                
            default:
                break;
        }
    }
}

void Network::setOpinionToAgents(){
    n_A = 0;
    n_B = 0;
    double randNum = 0.0;
    for (auto &node : nodeVec) {
        randNum = (double)rand()/RAND_MAX;
        if (randNum < 0.5) {
            node.setOpinionState(OPINION_A);
            n_A += 1;
        }else{
            node.setOpinionState(OPINION_B);
            n_B += 1;
        }
    }
}
void Network::resetOpinions(){
    n_A = 0;
    n_B = 0;
    for (auto &node : nodeVec) {
        node.setOpinionState(NULLOPINION);
    }
}

void Network::doVoterRule(){
    
    // select node
    int sNode1,sNode2;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0,totalNodes-1);
    
    sNode1 = dis(gen);
    
    if (nodeVec[sNode1].getDeg() == 0) {
        cout << "isolated node\n";
        return;
    }
    
    uniform_int_distribution<int> dis2(0,nodeVec[sNode1].getDeg() - 1);
    sNode2 = dis2(gen);
    
    // selected node index -> sNode1
    // n-th neighbor of sNode1 -> adjMax[sNode1][sNode2]
    
    // interaction
    cout << "nodePair (" << sNode1 << "," << adjMtx[sNode1][sNode2] << "):("
    << nodeVec[sNode1].getOpinionState()<< ","
    << nodeVec[adjMtx[sNode1][sNode2]].getOpinionState()<<") -> ";
    
    if (nodeVec[sNode1].getOpinionState() != nodeVec[adjMtx[sNode1][sNode2]].getOpinionState()) {
        // follow neighbor opinion
        switch (nodeVec[adjMtx[sNode1][sNode2]].getOpinionState()) {
            case OPINION_A:
                n_A += 1;
                n_B -= 1;
                break;
            case OPINION_B:
                n_A -= 1;
                n_B += 1;
                break;
            default:
                break;
        }
        nodeVec[sNode1].setOpinionState(nodeVec[adjMtx[sNode1][sNode2]].getOpinionState());
    }
    
    
    cout << "nodePair (" << sNode1 << "," << adjMtx[sNode1][sNode2] << "):("
    << nodeVec[sNode1].getOpinionState()<< ","
    << nodeVec[adjMtx[sNode1][sNode2]].getOpinionState()<<")";
    
    cout << "\n";
    
}

void Network::doMajorityRule(int __group){
    int group = __group;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0,totalNodes-1);
    vector<int> pool;
    int count = 0;
    int totalOpi = 0;
    
    while (count < group) {
        int node = dis(gen);
        if (pool.size() == 0) {
            pool.push_back(node);
            count++;
        }else{
            bool check = false;
            for (const int &item : pool) {
                if(item == node){
                    check = true;
                    break;
                }
            }
            if (check) {
                continue;
            }else{
                pool.push_back(node);
                count++;
            }
        }
    }
    
    for (const int &item : pool) {
        cout <<"(" << item << ","<<nodeVec[item].getOpinionState()<<"),";
        totalOpi +=nodeVec[item].getOpinionState();
    }
    cout << "   total : " << totalOpi << "\n";

    if (totalOpi > 0) {
        for (const int &item : pool) {
            if (nodeVec[item].getOpinionState() == OPINION_B) {
                nodeVec[item].setOpinionState(OPINION_A);
                n_A += 1;
                n_B -= 1;
            }
        }
    }else{
        for (const int &item : pool) {
            if (nodeVec[item].getOpinionState() == OPINION_A) {
                nodeVec[item].setOpinionState(OPINION_B);
                n_A -= 1;
                n_B += 1;
            }
        }
    }
    
}



int Network::getNumberOfA(){
    return n_A;
}

int Network::getNumberOfB(){
    return n_B;
}

void Network::setContinueousOpinionToAgents(){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);
    
    for (Agent &node : nodeVec) {
        node.setOpinionState(dis(gen));
    }
}

vector<Agent>& Network::getNodeVector(){
    return nodeVec;
}

vector<vector<int>>& Network::getAdjMtx(){
    return adjMtx;
}
