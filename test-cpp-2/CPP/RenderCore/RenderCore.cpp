//
//  RenderCode.cpp
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 19.10.24.
//

#include "RenderCore.hpp"
#include "UserCore.hpp"
#include "Blocks.hpp"
#include "vector"
#include "FileWork.hpp"
#include <iostream>
#include "cmath"

using namespace std;

float curHeight = 0, prevHeight = 0, getDown = 0;
int maxAnimation = 8;


float groundY = 0;

float curFloor = 0;
float blockFloor = 0;
CPPPoint blockStart = {0, 0};
CPPPoint blockEnd = {0, 0};
float curAnimation = 8;
bool isOnBlock = false;
int firstActiveBlock = 0;


std::vector<Block> platforms = { };

RenderCore::RenderCore(UserCore userCore) : userCore(userCore) { }

UserCore *usCore;

bool checkCollision(CPPSize size, CPPSize userSize, float currentJumpHeight) {
    return platforms[firstActiveBlock].blockType == CPPBlockType::platform ?
    (platforms[firstActiveBlock].start.x < 205 &&
     (size.height - userSize.height - 100 - currentJumpHeight - curFloor - 10 >
      size.height - userSize.height - 100 - blockFloor)) :
    
    (platforms[firstActiveBlock].start.x < 200 &&
     (platforms[firstActiveBlock].start.x + platforms[firstActiveBlock].end.x) / 2 > 200 &&
     currentJumpHeight + curFloor < 2 * (200 - platforms[firstActiveBlock].start.x) + platforms[firstActiveBlock].start.y)
    
    || ((platforms[firstActiveBlock].start.x + platforms[firstActiveBlock].end.x) / 2 < 200 &&
        (platforms[firstActiveBlock].start.x + platforms[firstActiveBlock].end.x) / 2 > 100 &&
        (currentJumpHeight + curFloor < platforms[firstActiveBlock].size.height + 2 + platforms[firstActiveBlock].floor)) ||
    
    ((platforms[firstActiveBlock].start.x + platforms[firstActiveBlock].end.x) / 2 < 100 &&
     platforms[firstActiveBlock].end.x > 100 &&
     currentJumpHeight + curFloor <  (100 - (platforms[firstActiveBlock].start.x + platforms[firstActiveBlock].end.x) / 2) * (platforms[firstActiveBlock].start.y - platforms[firstActiveBlock].start.y - platforms[firstActiveBlock].size.height) /
    (platforms[firstActiveBlock].end.x - (platforms[firstActiveBlock].start.x + platforms[firstActiveBlock].end.x) / 2) +
    platforms[firstActiveBlock].start.y + platforms[firstActiveBlock].size.height);
}

bool isDroppingDown = false;

float timeOfDropping = 0;



float currentBlockHeight = 0;

bool isDropping = false;

bool isJumpAvalable = true;

const float acceleration = 0.70;

const float START_SPEED = 16.775;

UserPoints userPoints;

FileWork fileWork;

constexpr float ROTATION_ANGLE = -7.5;

constexpr float CURRENT_ROTATION_HEIGHT = 50;

void userRotation(const int currentTick) {
    userPoints.leftDown.x = (100 - 150) * cos(ROTATION_ANGLE * currentTick * 3.14 / 180) + CURRENT_ROTATION_HEIGHT * sin(ROTATION_ANGLE * currentTick * 3.14 / 180) + 150;
    userPoints.leftDown.y = (100 - 150) * sin(ROTATION_ANGLE * currentTick * 3.14 / 180) - CURRENT_ROTATION_HEIGHT * cos(ROTATION_ANGLE * currentTick * 3.14 / 180) + CURRENT_ROTATION_HEIGHT;
    
    userPoints.leftUp.x = (100 - 150) * cos(ROTATION_ANGLE * currentTick * 3.14 / 180) - (100 - CURRENT_ROTATION_HEIGHT) * sin(ROTATION_ANGLE * currentTick * 3.14 / 180) + 150;
    userPoints.leftUp.y = (100 - 150) * sin(ROTATION_ANGLE * currentTick * 3.14 / 180) + (100 - CURRENT_ROTATION_HEIGHT) * cos(ROTATION_ANGLE * currentTick * 3.14 / 180) + CURRENT_ROTATION_HEIGHT;
    
    userPoints.rightUp.x = (200 - 150) * cos(ROTATION_ANGLE * currentTick * 3.14 / 180) - (100 - CURRENT_ROTATION_HEIGHT) * sin(ROTATION_ANGLE * currentTick * 3.14 / 180) + 150;
    userPoints.rightUp.y = (200 - 150) * sin(ROTATION_ANGLE * currentTick * 3.14 / 180) + (100 - CURRENT_ROTATION_HEIGHT) * cos(ROTATION_ANGLE * currentTick * 3.14 / 180) + CURRENT_ROTATION_HEIGHT;
    
    userPoints.rightDown.x = (200 - 150) * cos(ROTATION_ANGLE * currentTick * 3.14 / 180) + CURRENT_ROTATION_HEIGHT * sin(ROTATION_ANGLE * currentTick * 3.14 / 180) + 150;
    userPoints.rightDown.y = (200 - 150) * sin(ROTATION_ANGLE * currentTick * 3.14 / 180) - CURRENT_ROTATION_HEIGHT * cos(ROTATION_ANGLE * currentTick * 3.14 / 180) + CURRENT_ROTATION_HEIGHT;
}

const int TICK_AMOUNT = 25;
const int MAX_HEIGHT = 201;

float renderUserJump(const float curTime) {
    float jumpHeight = 0;
    if (usCore->isJumping) {
        usCore->isGravityProccessing = true;
        if (curTime < usCore->jumpTimeStart + TICK_AMOUNT) {
            const float deltaHeight = START_SPEED * (curTime - usCore->jumpTimeStart);
            jumpHeight = deltaHeight -
            acceleration * (curTime - usCore->jumpTimeStart) * (curTime - usCore->jumpTimeStart) / 2;
            usCore->jumpHeight = jumpHeight;
            userRotation(curTime - usCore->jumpTimeStart);
            
        } else {
            isJumpAvalable = false;
            usCore->isJumping = false;
            isDropping = true;
        }
    }
    if (isDropping) {
        jumpHeight = MAX_HEIGHT -
            acceleration * (curTime - usCore->jumpTimeStart - TICK_AMOUNT) * (curTime - usCore->jumpTimeStart - TICK_AMOUNT) / 2;
        if ((jumpHeight <= 10 && currentBlockHeight == curFloor) || jumpHeight + curFloor - currentBlockHeight <= 10) {
            usCore->isJumping = false;
            jumpHeight = 0;
            curFloor = blockFloor;
            usCore->currentTime = 24;
            isDropping = false;
            isJumpAvalable = true;
            usCore->isGravityProccessing = false;
        }
        if (blockFloor > curFloor && curFloor + jumpHeight > blockFloor && curFloor + jumpHeight - 10 < blockFloor) {
            usCore->isJumping = false;
            isDropping = false;
            jumpHeight = 0;
            usCore->currentTime = 24;
            curFloor = blockFloor;
            isJumpAvalable = true;
            usCore->isGravityProccessing = false;
        }
    }
    if (!isDropping && curHeight < curFloor && !usCore->isJumping) {
        usCore->isGravityProccessing = true;
        jumpHeight = - acceleration * timeOfDropping * timeOfDropping / 2;
        if (jumpHeight + curFloor - currentBlockHeight <= 5) {
            jumpHeight = 0;
            curFloor = curHeight;
            usCore->isGravityProccessing = false;
            isJumpAvalable = true;
        }
        timeOfDropping++;
    } else {
        timeOfDropping = 0;
    }
    return jumpHeight;
}


vector<Vertex> graph;



int curVertex = 0;

float currentBlockStart = 1000;


Vertex curNode;

void addEdge(int src, int dest, vector<CPPBlockType> blockTypes, vector<PositionAndSize> blockSizes) {
    graph[src].edgeArr.push_back(Edge(graph[src], graph[dest], blockSizes, blockTypes));
}


void addVertex(int index) {
    graph.push_back(Vertex(index, {}));
}

void createMap() {
    float lastPlatformX = 0;
    while (platforms.size() < 10) {
        if (!platforms.empty()) {
            currentBlockStart = platforms[platforms.size() - 1].end.x;
        }
        int nextVertex = rand() % curNode.edgeArr.size();
        for (int i = 0; i < curNode.edgeArr[nextVertex].blocks.size(); i++) {
            if (curNode.edgeArr[nextVertex].blockSizeAndPosition[i].position.y == 0) {
                platforms.push_back(Block(
                                          {currentBlockStart, 0},
                                          curNode.edgeArr[nextVertex].blocks[i],
                                          curNode.edgeArr[nextVertex].blockSizeAndPosition[i].size)
                                    );
                currentBlockStart += platforms[platforms.size() - 1].size.width;
                lastPlatformX = platforms[platforms.size() - 1].size.width;
            } else {
                platforms.push_back(Block(
                                          {currentBlockStart - lastPlatformX + curNode.edgeArr[nextVertex].blockSizeAndPosition[i].position.x, curNode.edgeArr[nextVertex].blockSizeAndPosition[i].position.y},
                                          curNode.edgeArr[nextVertex].blocks[i],
                                          curNode.edgeArr[nextVertex].blockSizeAndPosition[i].size)
                                    );
            }
        }
        curNode = graph[curNode.edgeArr[nextVertex].dest.index];
    }
}


void fillGraph() {
    if (graph.size() == 0) {
        srand(time(0));
        for (int i = 0; i < 9; i++) {
            addVertex(i);
        }
        addEdge(0, 1, {CPPBlockType::platform, CPPBlockType::triangle, CPPBlockType::spacer}, { {600, 70}, {{70,70}, {200, 70}},{200, 00} });
        addEdge(1, 2, {}, {});
        addEdge(0, 2, {CPPBlockType::triangle, CPPBlockType::spacer}, {{70, 70}, {400, 00}});
        addEdge(2, 4, {CPPBlockType::triangle, CPPBlockType::triangle, CPPBlockType::triangle, CPPBlockType::spacer}, {{70, 70}, {70, 70}, {70, 70}, {350, 0}});
        addEdge(2, 4, {CPPBlockType::triangle, CPPBlockType::triangle, CPPBlockType::spacer}, {{70, 70}, {70, 70}, {350, 0}});
        addEdge(0, 3, {CPPBlockType::platform, CPPBlockType::triangle, CPPBlockType::spacer}, {{600, 140}, {{70,70}, {300, 140}}, {500, 00}});
        addEdge(3, 4, {CPPBlockType::triangle, CPPBlockType::spacer}, {{70, 70}, {800, 00}});
        addEdge(4, 3, {CPPBlockType::platform, CPPBlockType::spacer, CPPBlockType::triangle, CPPBlockType::spacer}, {{400, 120}, {100, 00}, {70, 70}, {400, 00} });
        addEdge(4, 0, {CPPBlockType::platform, CPPBlockType::spacer}, {{400, 140}, {300, 0}});
        addEdge(3, 0, {CPPBlockType::triangle, CPPBlockType::spacer}, {{70, 70}, {200, 00}});
        addEdge(2, 0, {CPPBlockType::platform, CPPBlockType::spacer, CPPBlockType::platform, CPPBlockType::spacer, CPPBlockType::platform, CPPBlockType::spacer}, {{300, 100}, {150, 00}, {250, 200}, {150, 0}, {300, 300}, {300, 00}});
        addEdge(1, 0, {CPPBlockType::platform, CPPBlockType::spacer}, {{600, 70}, {400, 00}});
        addEdge(0, 5, {CPPBlockType::platform, CPPBlockType::spacer, CPPBlockType::platform, CPPBlockType::spacer, CPPBlockType::platform, CPPBlockType::spacer}, {{300, 100}, {150, 00}, {250, 200}, {150, 0}, {300, 300}, {150, 00}});
        addEdge(5, 6, {CPPBlockType::platform, CPPBlockType::triangle, CPPBlockType::triangle, CPPBlockType::spacer}, {{800, 300}, {{70, 70}, {200, 300}}, {{70, 70}, {600, 300}}, {400, 0}});
        addEdge(6, 0, {CPPBlockType::platform, CPPBlockType::spacer}, { {400, 70}, {200, 00} });
        addEdge(0, 7, {CPPBlockType::triangle, CPPBlockType::spacer, CPPBlockType::triangle, CPPBlockType::triangle, CPPBlockType::spacer}, {{70, 70}, {230, 0}, {70, 70}, {70, 70}, {350, 0}});
        addEdge(7, 0, {CPPBlockType::triangle, CPPBlockType::triangle, CPPBlockType::triangle, CPPBlockType::spacer}, {{70, 70}, {70, 70}, {70, 70}, {350, 0}});
        curNode = graph[0];
    }
}

constexpr CPPSize userSize = {100, 100};

constexpr int MAP_START = 1000;

CPPShape RenderCore::renderUser(const float jumpProgress, const CPPSize size, const bool isJumping, UserCore *userCore, const int curTime) {
    
    fillGraph();
    
    userPoints = {{100,0}, {100, 100}, {200, 100}, {200, 0}};
    
    createMap();
    usCore = userCore;
    CPPShape shape = CPPShape();
    bool isFound = false;
    for (int i = 0; i < platforms.size(); i++) {
        if (platforms[i].start.x < 170 && platforms[i].end.x > 100 && platforms[i].blockType == CPPBlockType::platform) {
            currentBlockHeight = platforms[i].size.height;
            isFound = true;
            break;
        }
    }
    if (!isFound) {
        currentBlockHeight = 0;
    }
    
    float currentJumpHeight = renderUserJump(curTime);
    if (firstActiveBlock < platforms.size() && checkCollision(size, userSize, currentJumpHeight)) {
        platforms = {};
        fileWork.appendFile(usCore->currentPoints);
        usCore->isAlive = false;
        curNode = graph[0];
        curFloor = 0;
        currentJumpHeight = 0;
        currentBlockStart = MAP_START;
        return CPPShape();
    }
    
    CPPPoints points = {
        {userPoints.leftUp.x, size.height - 100 - userPoints.leftUp.y  - curFloor - currentJumpHeight},
        {userPoints.rightUp.x, size.height - 100 - userPoints.rightUp.y - curFloor- currentJumpHeight},
        {userPoints.rightDown.x, size.height - 100 - userPoints.rightDown.y - curFloor- currentJumpHeight},
        {userPoints.leftDown.x, size.height - 100 - userPoints.leftDown.y - curFloor- currentJumpHeight},
        {userPoints.leftUp.x, size.height - 100 - userPoints.leftUp.y  - curFloor- currentJumpHeight},
    };
    shape.points = points;
    return shape;
}

CPPShape RenderCore::renderGround(const CPPSize size) {
    CPPShape shape = CPPShape();
    CPPPoints points = {
        {0, size.height - 100},
        {size.width, size.height - 100},
        {size.width, size.height},
        {0, size.height},
        {0,size.height - 100}
    };
    groundY = size.height - 100;
    shape.points = points;
    return shape;
}

int platformIndex = 0;

CPPShapes RenderCore::renderPlatform(const float platformProgress, const CPPSize fieldSize, const CPPSize blockSize) {
    for (int i = 0; i < platforms.size(); i++) {
        platforms[i].move();
    }
    CPPShapes shapes;
    
    for (int i = 0; i < platforms.size(); i++) {
        if (platforms[i].start.x < 70 && platforms[i].isActive) {
            platforms[i].isActive = false;
        } else if (platforms[i].isActive) {
            firstActiveBlock = i;
            break;
        }
    }
    
    for (int i = 0; i < platforms.size(); ++i) {
        if (platforms[i].end.x < 0) {
            platforms.erase(platforms.begin() + i);
        }
    }
    int firstPlatform = 0;
    for (int i = 0; i < platforms.size(); ++i) {
        if (platforms[i].blockType == CPPBlockType::platform && platforms[i].end.x > 100) {
            firstPlatform = i;
            break;
        }
    }
    if (!platforms.empty()) {
        if (platforms[firstPlatform].blockType == CPPBlockType::platform && platforms[firstPlatform].end.x > 100) {
            blockStart = platforms[firstPlatform].start;
            blockEnd = platforms[firstPlatform].end;
        }
        
        if (platforms[firstPlatform].start.x < 200 && platforms[firstPlatform].end.x > 100 && platforms[firstPlatform].blockType == CPPBlockType::platform) {
            curHeight = platforms[firstPlatform].size.height;
            blockFloor = platforms[firstPlatform].size.height;
            
        } else {
            curHeight = 0;
            blockFloor = 0;
        }
        int platform = 0;
        bool isFound = false;
        for (int i = 0; i < platforms.size(); ++i) {
            if (platforms[i].blockType == CPPBlockType::platform && platforms[i].end.x < 100) {
                platform = i;
                isFound = true;
                break;
            }
        }
        if (platform + 1 < platforms.size() && platforms[platform + 1].size.height < platforms[platform].size.height && platforms[platform].start.x < 100 && isFound) {
            curHeight = platforms[platform + 1].size.height;
        }
    }
    for (int i = 0; i < platforms.size(); i++) {
        if (platforms[i].blockType != CPPBlockType::triangle) {
            shapes.push_back(CPPShape({
                {platforms[i].start.x, fieldSize.height - 100 - platforms[i].size.height - platforms[i].start.y},
                {platforms[i].end.x, fieldSize.height - 100 - platforms[i].size.height - platforms[i].start.y},
                {platforms[i].end.x, fieldSize.height - 100 - platforms[i].start.y},
                {platforms[i].start.x, fieldSize.height - 100 - platforms[i].start.y},
                {platforms[i].start.x, fieldSize.height - 100 - platforms[i].size.height - platforms[i].start.y}
            }, platforms[i].blockType));
        } else {
            shapes.push_back(CPPShape({
                {platforms[i].start.x, fieldSize.height - 100 - platforms[i].start.y},
                {platforms[i].start.x + platforms[i].size.width / 2, fieldSize.height - 100 - platforms[i].size.height - platforms[i].start.y},
                {platforms[i].end.x, fieldSize.height - 100 - platforms[i].start.y},
                {platforms[i].start.x, fieldSize.height - 100 - platforms[i].start.y}
            }, platforms[i].blockType));
        }
    }
    return shapes;
}

