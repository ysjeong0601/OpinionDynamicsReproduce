//
//  NetworkEdge.hpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/07/27.
//

#ifndef NetworkEdge_hpp
#define NetworkEdge_hpp

#include <stdio.h>
#include <vector>

using namespace std;

class Edge{
    
private:
    bool state;
    pair<int, int> nodePair;
    double weight;

    
public:
    
    //constructor
    Edge(int _first, int _second, double _weight=0.0);
    
    bool isActivated();
    double getWeight();
    int getFirst();
    int getSecond();
    pair<int, int> getNodePair();
    
    void setActivation(bool _state);
    void setFisrt(int _first);
    void setSecond(int _second);
    void setWeight(double _weight);

    
};

#endif /* NetworkEdge_hpp */
