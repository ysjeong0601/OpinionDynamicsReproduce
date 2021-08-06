//
//  main.cpp
//  OpinionDynamics
//
//  Created by 정연수 on 2021/07/26.
//

#include <iostream>
#include "NetworkGenerator.hpp"
#include <string>
#include <filesystem>
#include "Deffuant.hpp"
#include "HegselmannKrause.hpp"
#include "Voter.hpp"
#include "Majority.hpp"

#define OPINION_A 1
#define OPINION_B -1

// for mac
using namespace std;
namespace fs = std::__fs::filesystem;

// for linux
//using namespace std::filesystem;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    string folderName = "result";
    
    string voterFileName = "voter_output";
    string mrfileName = "mr_output";
    string deffuant_file_name = "deffuant_output";
    string hk_file_name = "HK_output";
    
    
    
    Network network(false, 1000, 2000);
    network.setFullConnected(true);
    
    Voter voter(voterFileName);
    voter.setNetwork(network);
    voter.setFraction_A(0.5);
    voter.run(1000);
    
    cout << "voter done\n";
    
    Network network2(false,1000,2000);
    MajorityRule majority(mrfileName,3);
    majority.setNetwork(network2);
    
    network2.setFullConnected(true);
    majority.setFraction_A(0.55);
    majority.run(1000);
    
    cout << "mr done\n";
    
    Network network3(false,200,200);
    network3.setFullConnected(true);
    Deffuant deffuant(deffuant_file_name,0.5,0.15);
    
    deffuant.setNetwork(network3);
    deffuant.setRandomOpinion();
    deffuant.run(5000);
    cout << "deffuant done\n";
    
    Network network4(false,100,200);
    network4.setFullConnected(true);
    HegselmannKrause HK(hk_file_name, 0.2, 0.2);
    HK.setNetwork(network4);
    HK.setRandomOpinion();
    HK.run(5000);
    cout << "HK done\n";
    cout << "hk average : " << HK.getOpinionAverage()<<"\n";
    
    
    return 0;
}
