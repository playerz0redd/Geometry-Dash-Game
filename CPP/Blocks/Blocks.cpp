//
//  Blocks.cpp
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 19.10.24.
//

#include "Blocks.hpp"
#include "CPPModel.hpp"

#include "vector"

void Block::move() {
    if (isVisible) {
        moveProgress += 0.25;
        start.x -= 33.3 * 0.25;
        end.x -= 33.3 * 0.25;
    } else {
        isVisible = true;
    }
}

Block::Block(CPPPoint start, CPPBlockType blockType, CPPSize size) : start(start), blockType(blockType), size(size) {
    end.x = start.x + size.width;
    end.y = start.y;
    floor = start.y;
    
    if (blockType == CPPBlockType::spacer) {
        isActive = false;
    }
}
