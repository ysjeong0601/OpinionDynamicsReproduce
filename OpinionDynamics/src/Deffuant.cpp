//
//  Deffuant.cpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/08/01.
//
#include "NetworkGenerator.hpp"
#include "Deffuant.hpp"
#include "Opinion_Agent.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include <filesystem>

Deffuant::Deffuant(string __fileName, double __mu, double __epsilon){
    this->mu = __mu;
    this->epsilon = __epsilon;
    
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

void Deffuant::setNetwork(Network& __network){
    this->network = &__network;
    this->nodeVec = &__network.getNodeVector();
    this->adjMxt = &__network.getAdjMtx();
}

void Deffuant::setParameter(double __mu, double __epsilon){
    this->mu = __mu;
    this->epsilon = __epsilon;
}

void Deffuant::setRandomOpinion(){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);
    
    for (Agent &node : *nodeVec) {
        node.setOpinionState(dis(gen));
    }
    
}

void Deffuant::run(int __time){
    
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
        
        
        int sNode2 = dis2(gen);
        
        if (network->isFullConnected()) {
            sNode2 = dis(gen);
        }else{
            sNode2 = this->adjMxt->at(sNode1).at(sNode2);
            if (nodeVec->at(sNode1).getDeg() == 0) {
                step++;
                continue;
            }
        }
        
        double delta = 0.0;
        // opinion differenc => x_j - x_i
        delta = nodeVec->at(sNode2).getDoubleOpinionState() - nodeVec->at(sNode1).getDoubleOpinionState();
        
    
        // interaction
        if (abs(delta) < epsilon) {
            
            
            double op1,op2,dummy;
            dummy = mu * delta;
            op1 = nodeVec->at(sNode1).getDoubleOpinionState() + dummy;
            op2 = nodeVec->at(sNode2).getDoubleOpinionState() - dummy;
            nodeVec->at(sNode1).setOpinionState(op1);
            nodeVec->at(sNode2).setOpinionState(op2);
            
        }else{
            
        }
        
        fileStream << step << " ";
        for (Agent &node : *nodeVec) {
            fileStream << node.getDoubleOpinionState() << " ";
        }
        fileStream << "\n";
        
        step++;
    }
    fileStream.close();
}

double Deffuant::getOpinionAverage(){
    double average = 0.0;
    for (Agent &node : *nodeVec) {
        average += node.getDoubleOpinionState();
    }
    return average/network->getTotalNumberofNode();
}
