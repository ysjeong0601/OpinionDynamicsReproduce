//
//  AbstractInteration.hpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/08/08.
//

#ifndef AbstractInteration_hpp
#define AbstractInteration_hpp

#include "NetworkGenerator.hpp"
#include <stdio.h>

class Abstract_Interaction{
    
public:
    
    virtual void setNetwork(Network& __network) = 0;
    virtual double getOpinionAverage()=0;
    virtual void run(int __time)=0;
    virtual pair<int, int> getRandomPair()=0;
    
};

#endif /* AbstractInteration_hpp */
