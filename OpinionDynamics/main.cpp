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
#include "src/Deffuant.hpp"
#include "HegselmannKrause.hpp"
#include "Voter.hpp"
#include "Majority.hpp"
#include "Sznajd.hpp"

#define OPINION_A 1
#define OPINION_B -1


using namespace std;
// for mac
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
    string deg_dis_name = "degree_distribution";
    
//    Network network1(false,100,200);
//    Voter voter(network1,voterFileName);
//    voter.setFraction_A(0.6);
//    voter.run(100);
//
//    Network network2(false,100,200);
//    MajorityRule major(network2,voterFileName,3);
//    major.setFraction_A(0.6);
//    major.run(100);
//
//    Network network3(false,100,200);
//    Sznajd sznajd(network3,szFilename);
//    sznajd.setFraction_A(0.7);
//    sznajd.run(100);
//
//    Network network4(false,100,200);
//    Deffuant deffuant(network4,deffuant_file_name,0.4,0.2);
//    deffuant.run(10000);
    
    Network network5(false, 100, 200);
    HegselmannKrause hk(network5,hk_file_name,0.5,0.3);
    hk.run(50);
    cout << "done\n";
    
    return 0;
}
