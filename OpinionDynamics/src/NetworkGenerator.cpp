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
#include <algorithm>

#include "NetworkGenerator.hpp"

#define OPINION_A 1
#define OPINION_B -1
#define NULLOPINION 0

namespace fs = std::__fs::filesystem;

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

void Network::generate_Barabasi_Albert(int __init_deg, int __size){
    
    
    // start with 3 nodes
    if (!nodeVec.empty()) {
        cout << "network already exist\n";
        exit(1);
    }
    // init
    vector<int> degree_pool;
    int pool_size = 6;
    
    // create triangle
    addNode(0);
    addNode(1);
    addNode(2);
    int i=0;
    for (i=0; i<3; i++) {
        vector<int> row;
        adjMtx.push_back(row);
    }
    addEdge(0, 1);
    adjMtx[0].push_back(1);
    adjMtx[1].push_back(0);
    degree_pool.push_back(0);
    degree_pool.push_back(1);
    
    addEdge(0, 2);
    adjMtx[0].push_back(2);
    adjMtx[2].push_back(0);
    degree_pool.push_back(0);
    degree_pool.push_back(2);
    
    addEdge(1, 2);
    adjMtx[1].push_back(2);
    adjMtx[2].push_back(1);
    degree_pool.push_back(1);
    degree_pool.push_back(2);
    
    int index = 3;
    
    random_device rd;
    mt19937 gen(rd());
    while (index <= __size) {
        uniform_int_distribution<int> dis(0,pool_size-1); // init size = 6
        
        // add a node
        addNode(index);
        vector<int> newRow;
        adjMtx.push_back(newRow);
        
        // select nodes
        int addCount = 0;
        while (addCount < __init_deg) {
            if(adjMtx[index].empty()){
                int selected_Node = degree_pool[dis(gen)];
                addEdge(selected_Node,index);
                adjMtx[selected_Node].push_back(index);
                adjMtx[index].push_back(selected_Node);
                nodeVec[selected_Node].increaseDeg();
                nodeVec[index].increaseDeg();
                
                // pool update
                degree_pool.push_back(index);
                degree_pool.push_back(selected_Node);
            }else{
                int selected_Node = degree_pool[dis(gen)];
                // check repetition
                if (count(adjMtx[index].begin(), adjMtx[index].end(), selected_Node) == 0) {
                    addEdge(selected_Node, index);
                    adjMtx[selected_Node].push_back(index);
                    adjMtx[index].push_back(selected_Node);
                    nodeVec[selected_Node].increaseDeg();
                    nodeVec[index].increaseDeg();
                    
                    // pool update
                    degree_pool.push_back(index);
                    degree_pool.push_back(selected_Node);
                }else{
                    // repetition occur
                    continue;;
                }
            }
            addCount++;
        } // while (addCount < __init_deg)
        pool_size += 2*__init_deg;
        index++;
    } // while while (index <= 10000)
    totalNodes = (int)nodeVec.size();
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
    int i,j;
    for (i=0; i<(int)adjMtx.size();i++){
        cout << "index : " << i << " :";
        for (j=0; j<(int)adjMtx[i].size(); j++) {
            cout << " " << adjMtx[i][j];
        }
        cout << "\n";
    }
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
                break;
            default:
                cout << "\n";
                break;
        }
    }
}

void Network::fileOutput_Deg_dis(ofstream &__fileStream, string __fileName){
    int k;
    vector<int> degDis(totalNodes);
    
    string dummyFileName = __fileName.append(".txt");
    string folder = "result";
    
    fs::path filePath = fs::current_path();
    filePath/=folder;
    
    if (!fs::exists(filePath)) {
        fs::create_directory(filePath);
    }
    filePath /= dummyFileName;
    
    for (Agent &node : nodeVec) {
        degDis[node.getDeg()] += 1;
    }
    
    __fileStream.open(filePath);
    for (k=0; k<totalNodes; k++) {
        __fileStream << k << " " << degDis[k] << "\n";
    }
    __fileStream.close();
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

Network::~Network(){
    
}
