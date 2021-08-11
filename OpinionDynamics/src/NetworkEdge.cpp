//
//  NetworkEdge.cpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/07/27.
//

#include "NetworkEdge.hpp"
#define ACTIVATED 0;
#define INACTIVATED 1;


Edge::Edge(int _first, int _second,double _weight){
    this->state = ACTIVATED;
    this->nodePair.first = _first;
    this->nodePair.second = _second;
    this->weight = _weight;
}


bool Edge::isActivated(){
    return this->state;
}
double Edge::getWeight(){
    return this->weight;
}
int Edge::getFirst(){
    return this->nodePair.first;
}
int Edge::getSecond(){
    return this->nodePair.second;
}

pair<int, int> Edge::getNodePair(){
    return this->nodePair;
}

void Edge::setActivation(bool _state){
    this->state = _state;
}
void Edge::setFisrt(int _first){
    this->nodePair.first=_first;
}
void Edge::setSecond(int _second){
    this->nodePair.second = _second;
}
Edge::~Edge(){
    
}
