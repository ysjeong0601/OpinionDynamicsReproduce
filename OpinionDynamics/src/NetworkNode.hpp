//
//  NetworkNode.hpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/07/27.
//

#ifndef NetworkNode_hpp
#define NetworkNode_hpp

#include <stdio.h>

class Node{
    
protected:
    int index;
    int deg;
    double weight;
    bool state;
    
    
public:
    
    //constructor
    Node(int _index);
    
    
    bool isActivated();
    
    int getIndex();
    int getDeg();
    double getWeight();
    
    void setActivation(bool __isActivated);
    void setDegree(int __degree);
    void setWeight(double __weight);
    void increaseDeg(int __deg = 1);
    void decreaseDeg(int __deg = 1);
    
    virtual ~Node();
};

#endif /* NetworkNode_hpp */
