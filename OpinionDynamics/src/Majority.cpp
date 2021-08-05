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

void MajorityRule::setDebateGroup(int __group){
    this->debate_group = __group;
}

void MajorityRule::setNetwork(Network &__network){
    this->network = &__network;
    this->nodeVec = &__network.getNodeVector();
    this->adjMxt = &__network.getAdjMtx();
}

double MajorityRule::getOpinionAverage(){
    return (double)(n_A - n_B)/network->getTotalNumberofNode();
}

void MajorityRule::setFraction_A(double __fraction){
    int init_A = __fraction * network->getTotalNumberofNode();
    int assign_count = 0;
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

void MajorityRule::run(int __time){
    
    if (!fileStream.is_open()) {
        fileStream.open(filePath);
    }
    
    int step = 0;
    int time = __time;
    int sNode1 = 0 , allOpinion = 0;
    
    vector<Agent> group_vector;
    vector<int> avoiding_repetition;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0,network->getTotalNumberofNode()-1);
   
    fileStream << step  << " " << (double)n_A/network->getTotalNumberofNode() << " " << (double)n_B/network->getTotalNumberofNode() << "\n";
    step++;
    
    while (step < time) {
        int count = 0;
        bool check = false;
        
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
        
        step++;
    }
    
    
    
}
