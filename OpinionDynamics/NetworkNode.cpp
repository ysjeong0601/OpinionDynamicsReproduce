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

void Node::setActivation(bool _isActivated){
    this->state = _isActivated;
}
void Node::setDegree(int _degree){
    this->deg = _degree;
}
void Node::setWeight(double _weight){
    this->weight = _weight;
}
void Node::increaseDeg(){
    this->deg += 1;
}
void Node::decreaseDeg(){
    this->deg -= 1;
}
