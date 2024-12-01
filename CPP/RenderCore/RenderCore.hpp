//
//  RenderCode.hpp
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 19.10.24.
//

#ifndef RenderCore_hpp
#define RenderCore_hpp


#include "CPPModel.hpp"
#include "UserCore.hpp"
#include <stdio.h>

class RenderCore {
public:
    CPPShape renderUser(float jumpProgress, CPPSize renderSize, bool isJumping, UserCore *userCore, int curTime);
    CPPShape renderGround(CPPSize size);
    CPPShapes renderPlatform(float platformProgress, CPPSize fieldSize, CPPSize blockSize);
    UserCore userCore;
    
    RenderCore(UserCore userCore);
};

#endif /* RenderCode_hpp */
