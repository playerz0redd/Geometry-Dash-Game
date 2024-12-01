//Copyright © 2024 RealtBy. All rights reserved.

#ifndef CPPModel_h
#define CPPModel_h

#include "vector"

struct CPPPoint {
    float x = 0;
    float y = 0;
};



struct UserPoints {
    CPPPoint leftDown;
    CPPPoint leftUp;
    CPPPoint rightUp;
    CPPPoint rightDown;
};

struct CPPSize {
    float width, height;
};

enum class CPPBlockType {
    platform = 0,
    spacer,
    triangle,
    casesAmount = 3
};

struct CPPInt {
    int num;
};

typedef std::vector<CPPInt> CPPIntArray;

typedef std::vector<CPPPoint> CPPPoints;

typedef std::string CPPString;

struct CPPShape {
    CPPPoints points;
    CPPBlockType blockType;
};

struct Edge;

struct PositionAndSize {
    CPPSize size;
    CPPPoint position;
};

struct Vertex {
    int index;
    std::vector<Edge> edgeArr;
};

struct Edge {
    Vertex source;
    Vertex dest;
    std::vector<PositionAndSize> blockSizeAndPosition;
    std::vector<CPPBlockType> blocks;
};


typedef std::vector<CPPShape> CPPShapes;



#endif /* CPPModel_h */
