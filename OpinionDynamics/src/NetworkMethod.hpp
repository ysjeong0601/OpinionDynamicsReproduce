//
//  NetworkMethod.hpp
//  BaseNetwork
//
//  Created by 정연수 on 2021/06/07.
//

#ifndef NetworkMethod_hpp
#define NetworkMethod_hpp

#include <stdio.h>
class NetworkMethod{
public:
    
    virtual void addNode(int index)=0;
    virtual void addEdge(int first, int second)=0;
    
    //get
    virtual int getTotalNumberofNode()=0;
    virtual int getTotalNumberofEdge()=0;
    virtual int getTotalNumberofDegree()=0;
    
    // print
    virtual void printAllNode()=0;
    virtual void printAllEdge()=0;
    virtual void printAdjacency()=0;
};



#endif /* NetworkMethod_hpp */
