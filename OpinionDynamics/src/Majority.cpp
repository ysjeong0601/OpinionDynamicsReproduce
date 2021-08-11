//
//  Majority.cpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/08/03.
//

#include "Majority.hpp"
#include "NetworkGenerator.hpp"
#include <iostream>
#include <random>
#include <string>
#include <vector>

#define OPINION_A 1
#define OPINION_B -1

MajorityRule::MajorityRule(string __fileName, int __group){
    this->debate_group = __group;
    
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

MajorityRule::MajorityRule(Network& __network,string __fileName, int __group) : MajorityRule(__fileName, __group) {
    setNetwork(__network);
}

void MajorityRule::setDebateGroup(int __group){
    this->debate_group = __group;
}

void MajorityRule::setNetwork(Network &__network){
    this->network = &__network;
    this->nodeVec = &__network.getNodeVector();
    this->adjMxt = &__network.getAdjMtx();
    setFraction_A(0.5);
}

double MajorityRule::getOpinionAverage(){
    return abs((double)(n_A - n_B)/network->getTotalNumberofNode());
}


pair<int, int> MajorityRule::getRandomPair(){
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

void MajorityRule::setFraction_A(double __fraction){
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

void MajorityRule::run(int __time){
    
    if (!fileStream.is_open()) {
        fileStream.open(filePath);
    }
    
    int step = 0;
    int time = __time;
    int sNode1 = 0 , allOpinion = 0;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0,network->getTotalNumberofNode()-1);
   
    fileStream << step  << " " << (double)n_A/network->getTotalNumberofNode() << " " << (double)n_B/network->getTotalNumberofNode() << "\n";
    step++;
    
    while (step < time) {
        int count = 0;
        allOpinion = 0;
        bool check = false;
        vector<int> avoiding_repetition;
        vector<Agent> group_vector;
        
        // selected debate group
        while (count < debate_group) {
            sNode1 =  dis(gen);
            check = false;
            for (int &item : avoiding_repetition) {
                if (sNode1 == item) {
                    check = true;
                    break;
                }
            }
            // repetition
            if (check) {
                continue;
            }else{
                avoiding_repetition.push_back(sNode1);
                group_vector.push_back(nodeVec->at(sNode1));
                count++;
            }
        }
        
        for (Agent &node : group_vector) {
            allOpinion += node.getOpinionState();
        }
        
        // follow majority
        if (allOpinion > 0) {
            for (Agent &node : group_vector) {
                if (node.getOpinionState() != OPINION_A) {
                    node.setOpinionState(OPINION_A);
                    n_A += 1;
                    n_B -= 1;
                }
            }
        }else if(allOpinion < 0){
            for (Agent &node : group_vector) {
                if (node.getOpinionState() != OPINION_B) {
                    node.setOpinionState(OPINION_B);
                    n_A -= 1;
                    n_B += 1;
                }
            }
        }else{
            cout << "exception\n";
            exit(1);
        }
        
        fileStream << step  << " " << (double)n_A/network->getTotalNumberofNode() << " " << (double)n_B/network->getTotalNumberofNode() << " " << getOpinionAverage() << "\n";
        
        if (n_A == 0 || n_B == 0) {
            break;
        }
        step++;
    }
}
MajorityRule::~MajorityRule(){
    
}
