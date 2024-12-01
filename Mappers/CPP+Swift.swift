//
//  CPP+Swift.swift
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 19.10.24.
//

import Foundation

extension CPPPoints: RandomAccessCollection {
    public var startIndex: Int { 0 }
    public var endIndex: Int { size() }
}

extension CPPShape {
    var mappedPoints: [CPPPoint] {
        [CPPPoint](points)
    }
}

extension CPPPoint {
    var toCGPoint: CGPoint {
        .init(x: CGFloat(x), y: CGFloat(y))
    }
}

extension CPPInt {
    var toInt: Int {
        .init(num)
    }
}

extension CPPString {
    var toString: String {
        String(self)
    }
}

extension CPPShapes: RandomAccessCollection {
    public var startIndex: Int { 0 }
    public var endIndex: Int { size() }
}

extension CPPIntArray: RandomAccessCollection {
    public var startIndex: Int { 0 }
    public var endIndex: Int { size() }
}

extension CPPBlockType: RandomAccessCollection {
    public var startIndex: Int { return 0 }
    public var endIndex: Int { return Self.casesAmount.count }
    
    public subscript(index: Int) -> CPPBlockType {
        return Self.casesAmount[index]
    }
}


extension CGSize {
    var toCPPSize: CPPSize {
        .init(width: Float(width), height: Float(height))
    }
}
