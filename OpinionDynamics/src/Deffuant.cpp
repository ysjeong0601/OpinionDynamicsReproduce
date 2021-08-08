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

Deffuant::Deffuant(Network& __network,string __fileName, double __mu, double __epsilon) : Deffuant(__fileName,__mu,__epsilon){
    setNetwork(__network);
}


void Deffuant::setNetwork(Network& __network){
    this->network = &__network;
    this->nodeVec = &__network.getNodeVector();
    this->adjMxt = &__network.getAdjMtx();
    setRandomOpinion();
}

double Deffuant::getOpinionAverage(){
    double average = 0.0;
    for (Agent &node : *nodeVec) {
        average += node.getDoubleOpinionState();
    }
    return abs(average/network->getTotalNumberofNode());
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

pair<int, int> Deffuant::getRandomPair(){
    int sNode1 = 0,sNode2 = 0;
    pair<int, int> randomPair;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis1(0,network->getTotalNumberofNode()-1)
    ,dis2;
    
    if (network->isFullConnected()) {
        while (sNode1 == sNode2) {
            sNode1 = dis1(gen);
            sNode2 = dis2(gen);
        }
    }else{
        sNode1 = dis1(gen);
        if (nodeVec->at(sNode1).getDeg() == 0) {
            throw 0;
        }
        dis2 =uniform_int_distribution<int>(0,nodeVec->at(sNode1).getDeg()-1);
        sNode2 = dis2(gen);
        sNode2 = adjMxt->at(sNode1).at(sNode2);
    }
    randomPair.first = sNode1;
    randomPair.second = sNode2;
    
    return randomPair;
}



void Deffuant::run(int __time){
    
    // check stream
    if (!fileStream.is_open()) {
        fileStream.open(filePath);
    }
    
    int step = 0;
    int time = __time;
    pair<int, int> randomPair;
    int sNode1 =0, sNode2=0;
    
    
    // initial state
    // a row represents state of all node
    fileStream << step;
    for (Agent &node : *nodeVec) {
        fileStream << node.getDoubleOpinionState() << " ";
    }
    
    
    
    while (step < time) {
        try {
            randomPair = getRandomPair();
        } catch (int exception) {
            step++;
            continue;
        }
        sNode1 = randomPair.first;
        sNode2 = randomPair.second;
        
        double delta = 0.0;
        // opinion differenc => x_j - x_i
        delta = nodeVec->at(sNode2).getDoubleOpinionState() - nodeVec->at(sNode1).getDoubleOpinionState();
        
    
        // interact under conditions
        if (abs(delta) < epsilon) {
            double op1,op2,dummy;
            dummy = mu * delta;
            op1 = nodeVec->at(sNode1).getDoubleOpinionState() + dummy;
            op2 = nodeVec->at(sNode2).getDoubleOpinionState() - dummy;
            nodeVec->at(sNode1).setOpinionState(op1);
            nodeVec->at(sNode2).setOpinionState(op2);
            
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

