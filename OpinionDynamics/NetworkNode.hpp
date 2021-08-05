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
    
    void setActivation(bool _isActivated);
    void setDegree(int _degree);
    void setWeight(double _weight);
    void increaseDeg();
    void decreaseDeg();
};

#endif /* NetworkNode_hpp */
