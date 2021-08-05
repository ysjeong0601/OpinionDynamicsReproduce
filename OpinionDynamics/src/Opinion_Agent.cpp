//
//  Opinion_Agent.cpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/07/27.
//

#include "Opinion_Agent.hpp"

Agent::Agent(int _agent_index,int _opinion) : Node(_agent_index){
    this->opi_state = _opinion;
}

void Agent::setOpinionState(int __opinion){
    this->opi_state = __opinion;
}

void Agent::setOpinionState(double __opinion){
    this->double_opi_state = __opinion;
}

int Agent::getOpinionState(){
    return this->opi_state;
}

double Agent::getDoubleOpinionState(){
    return this->double_opi_state;
}
