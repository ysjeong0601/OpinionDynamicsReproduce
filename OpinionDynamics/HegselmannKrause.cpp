//
//  HegselmannKrause.cpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/08/02.
//
#include <iostream>
#include <random>
#include "HegselmannKrause.hpp"

HegselmannKrause::HegselmannKrause(string __fileName, double __mu, double __epsilon):Deffuant(__fileName, __mu, __epsilon){
    
}

void HegselmannKrause::setNetwork(Network &__network){
    Deffuant::setNetwork(__network);
}

void HegselmannKrause::setParameter(double __mu, double __epsilon){
    Deffuant::setParameter(__mu, __epsilon);
}

double HegselmannKrause::getOpinionAverage(){
    return Deffuant::getOpinionAverage();
}

void HegselmannKrause::run(int __time){
    // check stream
    if (!fileStream.is_open()) {
        fileStream.open(filePath);
    }
    
    int step = 0;
    int time = __time;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0,network->getTotalNumberofNode()-1);
    
    
    fileStream << step;
    // initial state
    // a row represents state of all node
    for (Agent &node : *nodeVec) {
        fileStream << node.getDoubleOpinionState() << " ";
    }
    
    
    
    while (step < time) {
        // select one;
        int sNode1 = dis(gen);
        
        // select one neighbor
        uniform_int_distribution<> dis2(0,nodeVec->at(sNode1).getDeg()-1);
        
        if (nodeVec->at(sNode1).getDeg() == 0) {
//            step++;
            continue;
        }
        int sNode2 = dis2(gen);
        
        if (network->isFullConnected()) {
            sNode2 = dis(gen);
        }else{
            sNode2 = this->adjMxt->at(sNode1).at(sNode2);
        }
        
        
        
    
        // interaction
        int node1_deg = nodeVec->at(sNode1).getDeg();
        int interaction_Count = 0;
        double sum = 0.0;
        int i = 0;
        for (i = 0; i < node1_deg; i++) {
            double delta = 0.0;
            sNode2 = nodeVec->at(adjMxt->at(sNode1).at(i)).getIndex();
            // opinion differenc => x_j - x_i
            delta = nodeVec->at(sNode2).getDoubleOpinionState() - nodeVec->at(sNode1).getDoubleOpinionState();
            
            if (abs(delta) < epsilon) {
                sum += nodeVec->at(sNode2).getDoubleOpinionState() - mu * delta;
                interaction_Count += 1;
            }
        }
        
        nodeVec->at(sNode1).setOpinionState(sum/interaction_Count);
        
        fileStream << step << " ";
        for (Agent &node : *nodeVec) {
            fileStream << node.getDoubleOpinionState() << " ";
        }
        fileStream << "\n";
        
        step++;
    }
    fileStream.close();
}
