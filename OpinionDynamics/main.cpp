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
#include "Sznajd.hpp"

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
    string szFilename = "sz_output";
    string deffuant_file_name = "deffuant_output";
    string hk_file_name = "HK_output";
    
    
    Network network1(false,100,20);
    Voter voter(voterFileName);
    voter.setNetwork(network1);
    // option
    voter.setFraction_A(0.5);
    
    voter.run(1000);
    cout << " done\n";
    
    
    Network network2(false,100,20);
    MajorityRule majorRule = MajorityRule(mrfileName, 3);
    // or
    //MajorityRule majorRule = MajorityRule(network2,mrfileName, 3);
    majorRule.setNetwork(network2); // when call setNetwork , setFraction_A(0.5) is also executed
    majorRule.setFraction_A(0.5);
    majorRule.run(100);
    cout << "mr done\n";
    
    
    Network network3(false, 100,200);
    Sznajd sznajd = Sznajd(szFilename);
    sznajd.setNetwork(network3);
    sznajd.setFraction_A(0.5);
    sznajd.run(100);
    cout << "sz done\n";
    
    Network network4(false,100,200);
    Deffuant deffuant = Deffuant(deffuant_file_name, 0.2, 0.2);
    deffuant.setNetwork(network4);
    deffuant.run(1000);
    
    
    Network network5(false,100,200);
    HegselmannKrause hk = HegselmannKrause(hk_file_name, 0.2, 0.2);
    hk.setNetwork(network5);
    hk.run(1000);
    
    return 0;
}
