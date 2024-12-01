//
//  UserCore.hpp
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 19.10.24.
//

#ifndef UserCore_hpp
#define UserCore_hpp

#include <stdio.h>
#include "CPPModel.hpp"
#include "vector"
#include "FileWork.hpp"

class UserCore : public FileWork {
public:
    void jump(int time);
    void addPoints();
    std::vector<int> recordsArr;
    bool isAlive = true;
    int currentPoints = 0;
    float jumpProgress;
    bool isJumping = false;
    float currentHeight = 0;
    float jumpHeight = 0;
    float jumpTimeStart = 0;
    float currentTime = 0;
    bool isGravityProccessing = false;
};

#endif /* UserCore_hpp */
