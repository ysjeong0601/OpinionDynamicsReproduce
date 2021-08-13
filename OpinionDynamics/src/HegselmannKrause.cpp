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

HegselmannKrause::HegselmannKrause(Network& __network, string __fileName, double __mu, double __epsilon):Deffuant(__network,__fileName, __mu, __epsilon){
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

pair<int, int> HegselmannKrause::getRandomPair(){
    return Deffuant::getRandomPair();
}

void HegselmannKrause::run(int __time){
    for (Agent &node : *nodeVec) {
        prev_state_vector.push_back(node.getDoubleOpinionState());
    }
    
    // check stream
    if (!fileStream.is_open()) {
        fileStream.open(filePath);
    }
    
    int step = 0;
    int time = __time;
    int sNode1 = 0, sNode2 = 0;
    
    fileStream << step;
    // initial state
    // a row represents state of all node
    for (Agent &node : *nodeVec) {
        fileStream << node.getDoubleOpinionState() << " ";
    }
    
    
    
    while (step < time) {
        
        int node1_deg;
        int interaction_Count = 0;
        double sum = 0.0;
        
        // for all nodes, synchronous
        for (Agent &node : *nodeVec) {
            if (node.getDeg() == 0) {
                continue;
            }
            sNode1 = node.getIndex();
            node1_deg = nodeVec->at(sNode1).getDeg();
            interaction_Count = 0;
            sum = 0.0;
            
            if (network->isFullConnected()) {
                int i = 0;
                for (i = 0; i < network->getTotalNumberofNode(); i++) {
                    if (i == sNode1) {
                        continue;
                    }
                    double delta = 0.0;
                    sNode2 = nodeVec->at(i).getIndex();
                    // opinion differenc => x_j - x_i
                    delta = nodeVec->at(sNode2).getDoubleOpinionState() - nodeVec->at(sNode1).getDoubleOpinionState();
                    
                    if (abs(delta) < epsilon) {
                        sum += nodeVec->at(sNode2).getDoubleOpinionState() - mu * delta;
                        interaction_Count += 1;
                    }
                }
            }else{
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
            }
            if (interaction_Count != 0) {
                prev_state_vector[sNode1] = sum/interaction_Count;
            }
        } // for - range
        
        // update
        for (Agent &node : *nodeVec) {
            node.setOpinionState(prev_state_vector[node.getIndex()]);
        }
        
        // writhe
        fileStream << step << " ";
        for (Agent &node : *nodeVec) {
            fileStream << node.getDoubleOpinionState() << " ";
        }
        fileStream << "\n";
        
        step++;
    }
    fileStream.close();
    
}

HegselmannKrause::~HegselmannKrause(){
    
}
