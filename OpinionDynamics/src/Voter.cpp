//
//  Voter.cpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/08/03.
//

#include "NetworkGenerator.hpp"
#include "Opinion_Agent.hpp"
#include "Voter.hpp"
#include <iostream>
#include <random>
#include <filesystem>
#include <string>

#define OPINION_A 1
#define OPINION_B -1
#define NULLOPINION 0

namespace fs = std::__fs::filesystem;

Voter::Voter(string __fileName){
    
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

void Voter::setNetwork(Network &__network){
    this->network = &__network;
    this->nodeVec = &__network.getNodeVector();
    this->adjMxt = &__network.getAdjMtx();
    
    n_A = this->network->getTotalNumberofNode();
    n_B = 0;
}

double Voter::getOpinionAverage(){
//    double sum = 0.0;
//    for (Agent &node : *nodeVec) {
//        sum += node.getOpinionState();
//    }
//    return sum/network->getTotalNumberofNode();
    return (double)(n_A - n_B)/network->getTotalNumberofNode();
}

void Voter::run(int __time){
    
    if (!fileStream.is_open()) {
        fileStream.open(filePath);
    }
    
    int step = 0;
    int time = __time;
    int sNode1 , sNode2;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0,network->getTotalNumberofNode()-1);
    
    
    
    
    fileStream << step  << " " << (double)n_A/network->getTotalNumberofNode() << " " << (double)n_B/network->getTotalNumberofNode() << "\n";
    step++;
    while (step < time) {
        
        sNode1 = dis(gen);
        
        if (nodeVec->at(sNode1).getDeg() == 0) {
            continue;
        }
        
        if (network->isFullConnected() == true) {
            sNode2 = dis(gen);
        }else{
            uniform_int_distribution<int> dis2(0,nodeVec->at(sNode1).getDeg()-1);
            sNode2 = dis2(gen);
            sNode2 = adjMxt->at(sNode1).at(sNode2);
        }
        
        
        if (nodeVec->at(sNode1).getOpinionState() != nodeVec->at(sNode2).getOpinionState()) {
            // a neighbor node j changes selected node i's opinion
            switch (nodeVec->at(sNode2).getOpinionState()) {
                case OPINION_A:
                    n_A += 1;
                    n_B -= 1;
                    break;
                    
                case OPINION_B:
                    n_A -= 1;
                    n_B += 1;
                    break;
                default:
                    cout << "error\n";
                    exit(1);
                    break;
            }
        }
        
        fileStream << step  << " " << (double)n_A/network->getTotalNumberofNode() << " " << (double)n_B/network->getTotalNumberofNode() << " " << getOpinionAverage() << "\n";
        
        step++;
        
    }
    
    if (fileStream.is_open()) {
        fileStream.close();
    }
    
}

void Voter::setFraction_A(double __fraction){
    int assign_count = 0;
    int init_A = __fraction * network->getTotalNumberofNode();
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0,(network->getTotalNumberofNode())-1);
    
    
    if(n_A != 0 || n_B != 0){
        n_A = 0;
        n_B = 0;
    }
    
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
