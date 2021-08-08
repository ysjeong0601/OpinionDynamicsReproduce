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
    pair<int, int> nodePair;
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
            nodePair = selectNodePair();
            sNode1 = nodePair.first;
            sNode2 = nodePair.second;
            
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

pair<int, int> Network::selectNodePair(){
    int sNode1 = 0,sNode2 = 0;
    pair<int, int> randomPair;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis1(0,totalNodes-1);
    
    while (sNode1 == sNode2) {
        sNode1 = dis1(gen);
        sNode2 = dis1(gen);
    }
    randomPair.first = sNode1;
    randomPair.second = sNode2;
    
    return randomPair;
}

vector<Agent>& Network::getNodeVector(){
    return nodeVec;
}

vector<vector<int>>& Network::getAdjMtx(){
    return adjMtx;
}
