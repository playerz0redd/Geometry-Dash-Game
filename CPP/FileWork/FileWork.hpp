//
//  FileWork.hpp
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 23.11.24.
//

#ifndef FileWork_hpp
#define FileWork_hpp

#include <stdio.h>
#include <iostream>
#include "CPPModel.hpp"

using namespace std;

class FileWork {
    
    const char filePath[100] = "/Users/pavelplayerz0redd/Downloads/test-cpp-2/test-cpp-2/CPP/FileWork/records.txt";
public:
    std::vector<CPPInt> readFile();
    void appendFile(int record);
};

#endif /* FileWork_hpp */

