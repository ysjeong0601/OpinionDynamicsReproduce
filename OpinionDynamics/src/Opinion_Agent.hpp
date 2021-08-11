//
//  Opinion_Agent.hpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/07/27.
//

#ifndef Opinion_Agent_hpp
#define Opinion_Agent_hpp

#include <stdio.h>
#include "NetworkNode.hpp"

// agent with discrete opinion



class Agent : public Node{
private:
//    int opi_state;
    int opi_state{0};
    double double_opi_state{0.0};
public:
    Agent(int _agent_index,int _opinion = 1);
    void setOpinionState(int __state);
    void setOpinionState(double __state);
    int getOpinionState();
    double getDoubleOpinionState();
    
    virtual ~Agent();
};


#endif /* Opinion_Agent_hpp */
