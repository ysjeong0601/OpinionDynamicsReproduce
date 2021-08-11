//
//  Sznajd.cpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/08/06.
//

#include <iostream>
#include <random>
#include <string>
#include <queue>
#include <cmath>
#include "NetworkGenerator.hpp"
#include "Sznajd.hpp"

#define OPINION_A 1
#define OPINION_B -1

Sznajd::Sznajd(string __fileName){
    // set file location
    // project folder/result/data.txt
    string dummyFileName = __fileName.append(".txt");
    string folder = "result";
    filePath = fs::current_path();
    filePath/=folder;
    
    if (!fs::exists(filePath)) {
        fs::create_directory(filePath);
    }
    filePath /= dummyFileName;
    
}
Sznajd::Sznajd(Network& __network,string __fileStream) : Sznajd(__fileStream){
    setNetwork(__network);
    setFraction_A(0.5);
    if (__network.isFullConnected() == true) {
        cout << "complete network is not allowed";
        exit(1);
    }
}

void Sznajd::setNetwork(Network& __network){
    this->network = &__network;
    this->nodeVec = &__network.getNodeVector();
    this->adjMxt = &__network.getAdjMtx();
    setFraction_A(0.5);
}

void Sznajd::setFraction_A(double __fraction){
    int init_A = __fraction * network->getTotalNumberofNode();
    int assign_count = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0,(network->getTotalNumberofNode())-1);
    
    
    n_A = 0;
    n_B = 0;
    
    for (Agent &node : *nodeVec) {
        node.setOpinionState(OPINION_B);
        n_B += 1;
    }
    
    while (assign_count != init_A) {
        int node = dis(gen);
        if (nodeVec->at(node).getOpinionState() == OPINION_B) {
            nodeVec->at(node).setOpinionState(OPINION_A);
            assign_count += 1;
            n_A += 1;
            n_B -= 1;
        }
    }
}

double Sznajd::getOpinionAverage(){
    return abs((double)(n_A - n_B)/network->getTotalNumberofNode());
}

void Sznajd::run(int __time){
    // check stream
    if (!fileStream.is_open()) {
        fileStream.open(filePath);
    }
    
    int step = 0;
    int time = __time;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0,network->getTotalNumberofNode()-1);
    
    
    // write initial state
    fileStream << step << " " << (double)n_A/network->getTotalNumberofNode() << " " << (double)n_B/network->getTotalNumberofNode() << " " << getOpinionAverage() <<"\n";
    // initial state
    // a row represents state of all node
    
    int sNode1=0,sNode2=0;
    
    while (step < time || (n_A == 0 || n_B == 0)) {
        do {
            sNode1 = dis(gen);
        } while (nodeVec->at(sNode1).getDeg() == 0);
        uniform_int_distribution<> dis2(0,(nodeVec->at(sNode1).getDeg())-1);
        sNode2 = dis2(gen);
        sNode2 = adjMxt->at(sNode1).at(sNode2);
        
        // if two agents have different opinion
        if (nodeVec->at(sNode1).getOpinionState() != nodeVec->at(sNode2).getOpinionState()) {
            step++;
            continue;
        }
        
        queue<int> queue;
        // push all neighbors of agent 1 in queue
        for (int &index : adjMxt->at(sNode1)) {
            queue.push(index);
        }
        for (int &index : adjMxt->at(sNode2)) {
            queue.push(index);
        }
        
        switch (nodeVec->at(sNode1).getOpinionState()) {
            case OPINION_A:
                while (!queue.empty()) {
                    int index = queue.front();
                    if (nodeVec->at(index).getOpinionState() == OPINION_B) {
                        nodeVec->at(index).setOpinionState(OPINION_A);
                        n_A += 1;
                        n_B -= 1;
                    }
                    queue.pop();
                }
                break;
                
            case OPINION_B:
                while (!queue.empty()) {
                    int index = queue.front();
                    if (nodeVec->at(index).getOpinionState() == OPINION_A) {
                        nodeVec->at(index).setOpinionState(OPINION_B);
                        n_A -= 1;
                        n_B += 1;
                    }
                    queue.pop();
                }
                break;
                
            default:
                cout << "exception occured\n";
                break;
        }
        
        fileStream << step << " " << (double)n_A/network->getTotalNumberofNode() << " " << (double)n_B/network->getTotalNumberofNode() << " " << getOpinionAverage() <<"\n";
        
        
        if (n_A == 0 || n_B == 0) {
            break;
        }
        step++;
    } // while(step<time) end
    
    fileStream.close();
    
}

Sznajd::~Sznajd(){
    
}
