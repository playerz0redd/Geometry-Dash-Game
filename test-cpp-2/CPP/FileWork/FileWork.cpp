//
//  FileWork.cpp
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 23.11.24.
//

#include "FileWork.hpp"
#include <fstream>
#include <vector>
#include "stdlib.h"

void FileWork::appendFile(int record) {
    FILE *recordFile = fopen(this->filePath, "a");
    if (recordFile) {
        fprintf(recordFile, "%d ", record);
        fclose(recordFile);
    }
}

std::vector<CPPInt> FileWork::readFile() {
    std::vector<CPPInt> recordArr = {};
    std::ifstream recordFile(this->filePath);
    CPPInt record;
    if (recordFile) {
        while(!recordFile.eof()) {
            recordFile >> record.num;
            recordArr.push_back(record);
        }
        recordFile.close();
    }
    return recordArr;
}
