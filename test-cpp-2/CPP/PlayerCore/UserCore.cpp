//
//  UserCore.cpp
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 19.10.24.
//

#include "UserCore.hpp"
#include "CPPModel.hpp"
#include "fstream"
#include "iostream"

void UserCore::jump(int time) {
    if (!isJumping) {
        jumpTimeStart = time;
        isJumping = true;
    }
}

void UserCore::addPoints() {
    currentPoints += 1;
}




