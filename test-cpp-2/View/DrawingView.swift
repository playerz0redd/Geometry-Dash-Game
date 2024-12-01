//Copyright © 2024 RealtBy. All rights reserved.

import SwiftUI
import Combine
import AppKit
import AVFoundation

enum CurrentState {
    case error
    case menu
    case game
    case recordsMenu
}

enum BlockType: Int, CaseIterable {
    case platform
    case spacer
    case triagle
}

var recordsArr: [Int] = []


var currentSize: Double = 1
var isIncreasing = true

struct DrawingView: View {
    @StateObject var viewModel: DrawingViewModel = .init()
    @State var currentDate: Date = .init()
    @State var state: CurrentState = .menu
    @State var isAnimating = false;
    @State var timer = Timer.publish(every: 1 / 60, on: .main, in: .common).autoconnect()
    @State var time: Int = 0
    var audioPlayer: MusicCore = .init()
    var body: some View {
        VStack {
            if state == .recordsMenu {
                RecordsView(recordsArr: recordsArr, state: $state)
            }
            else if (state == .game && viewModel.userCore.isAlive) {
                    Canvas () { context, size in
                        drawGround(size: size, context: context)
                        let shapes = viewModel.renderCore
                            .renderPlatform(viewModel.renderBlock[0].moveProgress, size.toCPPSize, CPPSize(width: 1000, height: 100));
                        for i in 0..<shapes.count {
                            drawBlock(size: size, context: context, shape: shapes[i])
                            drawCircle(size: size, context: context, shape: shapes[i])
                        }
                        drawUser(size: size, context: context)
                    }
                    .id(currentDate)
                    .background(.linearGradient(
                        .init(colors: [
                            Color(red: 64/255, green: 64/255, blue: 64/255),
                            Color(red: 153 / 255, green: 0, blue: Double(time % 255 / 10)  / 255)]),
                        startPoint: .leading,
                        endPoint: .trailing))
                    .ignoresSafeArea()
                    .overlay(alignment: .topTrailing, content: {
                        Text("Points: \(viewModel.userCore.currentPoints)")
                            .font(.largeTitle)
                            .background(content: {
                                Capsule()
                                    .foregroundStyle(Color .cyan)
                                    .frame(minWidth: 140, minHeight: 45)
                                
                            })
                            .padding(.trailing, 40)
                            .padding(.top, 30)
                        
                    })
                }
                else if (state == .menu) {
                    GameMenu(viewModel: viewModel, state: $state, audioPlayer: audioPlayer)
                }
                else if (state == .error || !viewModel.userCore.isAlive) {
                    LoseView(state: $state, viewModel: viewModel, audioPlayer: audioPlayer)
                }
            
        }
        .onAppear {
            state = CurrentState.game
            viewModel.userCore.isAlive = true
            viewModel.userCore.currentPoints = 0
        }
        .onReceive(timer) { newDate in
            currentDate = newDate
            if (state == .game && viewModel.userCore.isAlive) {
                time += 1
                if (time % 10 == 0) {
                    viewModel.userCore.addPoints()
                }
                for i in 0..<viewModel.renderBlock.count {
                    viewModel.renderBlock[i].move()
                }
            }
        }
        .padding()
        .background(
            Button(action: {
                if (!viewModel.userCore.isGravityProccessing) {
                    time = 0
                    viewModel.userCore.currentTime = 0
                    viewModel.userCore.jump(Int32(time)) }
            }) {}
                .keyboardShortcut(.space, modifiers: [])
                .opacity(0)
        )
        
    }
}

// MARK: - Drawing

private extension DrawingView {
    func drawGround(
        size: CGSize,
        context: GraphicsContext
    ) {
        let path = NSBezierPath()
        let points = viewModel.renderCore
            .renderGround(size.toCPPSize)
            .mappedPoints.map(\.toCGPoint)
        path.move(to: points.first!)
        points.forEach {
            path.line(to: $0)
        }
        
        let drawingPath = Path(path.cgPath)
        context.fill(drawingPath, with: .linearGradient(
            .init(colors: [Color(red: 198/255, green: 0, blue: 67/255), Color(red: 255/255, green: 138/255, blue: 138/255)]),
            startPoint: .init(x: 0, y: size.height - 100),
            endPoint: .init(x: size.width, y: size.height))
        )
    }
    
    func drawUser(size: CGSize, context: GraphicsContext) {
        let path = NSBezierPath()

        let points = viewModel.renderCore
            .renderUser(viewModel.userCore.jumpProgress, size.toCPPSize, viewModel.userCore.isJumping, &viewModel.userCore, Int32(time))
            .mappedPoints.map(\.toCGPoint)
        guard !points.isEmpty
        else {
            state = .error
            return
        }
        path.move(to: points.first!)
        points.forEach {
            path.line(to: $0)
        }
        
        let drawingPath = Path(path.cgPath)
        context.fill(drawingPath, with: .linearGradient(
            .init(colors: [.indigo, .pink]),
            startPoint: .init(x: 100, y: size.height - 200),
            endPoint: .init(x: 200, y: size.height - 100))
        )
        if (!viewModel.userCore.isAlive) {
            state = .error
        }
    }
    
    func drawBlock(size: CGSize, context: GraphicsContext, shape: CPPShape) {
        let path = NSBezierPath()
        if state == .error {
            viewModel.renderBlock[0].moveProgress = 0
        }
        let points = shape.mappedPoints.map(\.toCGPoint)
        path.move(to: points.first!)
        points.forEach {
            path.line(to: $0)
        }
        let drawingPath = Path(path.cgPath)
        switch shape.blockType {
        case .triangle:
            context.fill(drawingPath, with: .linearGradient(
                .init(colors: [Color(red: 200/255, green: Double(time % 255 / 7)  / 255, blue: 250/250), Color(red: 103/255, green: 69/255, blue: 136/255)]),
                startPoint: .init(x: 150, y: size.height - 100),
                endPoint: .init(x: 200, y: size.height - 100))
            )
        case .platform:
            context.fill(drawingPath, with: .linearGradient(
                .init(colors: [Color(red: 4/255, green: 127/255 ,blue: 253/255), Color(red: 0/255, green: 86/255, blue: 112/255)]),
                startPoint: .init(x: 20, y: size.height - 50),
                endPoint: .init(x: 50, y: size.height - 20))
            )
        default:
            return;
        }
    }
    
    func drawCircle(size: CGSize, context: GraphicsContext, shape: CPPShape) {
        if (shape.blockType == .platform) {
            let points = shape.mappedPoints.map(\.toCGPoint)
            
            let xCoord = points[0].x
            let yCoord = points[0].y
            if isIncreasing {
                if currentSize > 133 {
                    isIncreasing.toggle()
                }
                else {
                    currentSize += 1
                }
            } else {
                if currentSize < 2 {
                    isIncreasing.toggle()
                } else {
                    currentSize -= 1
                }
            }
            
            let rect = CGRect(origin: CGPoint(x: xCoord + 20, y: yCoord - 150), size: CGSize(width: currentSize * 0.75, height: currentSize * 0.75))
            let drawingPath = Circle().path(in: rect)
            context.fill(drawingPath, with: .color(Color(red: (125 + currentSize) / 255, green: (75 + currentSize) / 255, blue: 0)))
        }
    }
    
        

}
