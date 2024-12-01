//
//  DrawingViewModel.swift
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 19.10.24.
//

import Combine

final class DrawingViewModel: ObservableObject {
    var userCore: UserCore
    var renderCore: RenderCore
    var renderBlock : [Block]
    
    init() {
        let userCore = UserCore()
        self.userCore = userCore
        self.renderCore = RenderCore(userCore)
        self.renderBlock = [Block()]
    }
}
