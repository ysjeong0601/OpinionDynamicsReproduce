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
    string deg_dis_name = "degree_distribution";
    
    Network network1(false,100,20);
    Voter voter(voterFileName);
    voter.setNetwork(network1);
    // option
    voter.setFraction_A(0.5);
    
    voter.run(1000);
    cout << " done\n";
    
    Network ba_network;
    ba_network.generate_Barabasi_Albert(2,100000);
    
    ofstream degStream;
    ba_network.fileOutput_Deg_dis(degStream, deg_dis_name);
    
    return 0;
}
