//
//  HegselmannKrause.hpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/08/02.
//

#ifndef HegselmannKrause_hpp
#define HegselmannKrause_hpp


#include "NetworkGenerator.hpp"
#include "Opinion_Agent.hpp"
#include "Deffuant.hpp"
#include <stdio.h>
#include <vector>

class HegselmannKrause : public Deffuant{
    
public:
    
    HegselmannKrause(string __fileName, double __mu, double __epsilon);
    void setNetwork(Network& __network);
    void setParameter(double __mu, double __epsilon);
    void run(int __time);
    double getOpinionAverage();
};



#endif /* HegselmannKrause_hpp */
