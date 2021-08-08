//
//  NetworkNode.cpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/07/27.
//

#include "NetworkNode.hpp"
#define ACTIVATED 1
#define INACTIVATED 0



Node::Node(int node_index){
    this->index = node_index;
    this->deg = 0;
    this->weight = 0.0;
    this->state = ACTIVATED;
};

bool Node::isActivated(){
    return this->state = INACTIVATED;
}

int Node::getIndex(){
    return this->index;
}
int Node::getDeg(){
    return this->deg;
}
double Node::getWeight(){
    return this->weight;
}

void Node::setActivation(bool __isActivated){
    this->state = __isActivated;
}
void Node::setDegree(int __degree){
    this->deg = __degree;
}
void Node::setWeight(double __weight){
    this->weight = __weight;
}
void Node::increaseDeg(int __deg){
    this->deg += __deg;
}
void Node::decreaseDeg(int __deg){
    this->deg -= __deg;
}
