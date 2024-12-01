//
//  Blocks.hpp
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 19.10.24.
//

#ifndef Blocks_hpp
#define Blocks_hpp

#include <stdio.h>
#include "CPPModel.hpp"

#endif /* Blocks_hpp */

class Block {
public:
    CPPBlockType blockType;
    CPPSize size = {100, 100};
    CPPPoint start = {1000, 0};
    CPPPoint end = {1000 + size.width, start.y};
    float floor = start.y;
    bool isVisible = false;
    bool isActive = true;
    float moveProgress = 0;
    void move();
    
    Block(CPPPoint start, CPPBlockType blockType, CPPSize size);
};
