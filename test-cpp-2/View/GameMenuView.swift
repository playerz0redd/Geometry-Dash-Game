//
//  GameMenuView.swift
//  test-cpp-2
//
//  Created by Pavel Playerz0redd on 25.11.24.
//

import Foundation
import SwiftUI

struct GameMenu: View {
    @StateObject var viewModel: DrawingViewModel
    @Binding var state: CurrentState
    var audioPlayer: MusicCore
    @State var isPlaying = false
    @State var isShowing = false
    var body: some View {
        Image("geometryBackground")
            .resizable()
            .scaledToFill()
            .ignoresSafeArea()
            .overlay(alignment: .top) {
                VStack {
                    MenuText(size: 100, colorTop: Color(red: 255/255, green: 62/255, blue: 159/255), colorBottom: Color(red: 254/255, green: 69/255, blue: 11/255), text: "GEOMETRY\n DASH")
                        .padding(.top, 100)
                        .padding(.bottom, 60)
                        
    
                    Button {
                        state = CurrentState.game
                        viewModel.userCore.isAlive = true
                        viewModel.userCore.currentPoints = 0
                    } label: {
                        MenuButtonView(text: "START")
                    }.buttonStyle(PlainButtonStyle())
                        .padding(.vertical, 30)
                    
                
                    Button {
                        state = .recordsMenu
                    } label: {
                        MenuButtonView(text: "RECORD")
                    }
                    .buttonStyle(PlainButtonStyle())
                    .padding(.bottom, 30)
                    
                    
                    Button {
                        if !audioPlayer.isPlaying {
                            audioPlayer.playMusic()
                        } else {
                            audioPlayer.stopMusic()
                        }
                        isPlaying.toggle()
                    } label: {
                        MenuButtonView(text: !isPlaying ? "MUSIC ON" : "MUSIC OFF")
                    }.buttonStyle(PlainButtonStyle())
                }
                Spacer()
            }
            .ignoresSafeArea()
            .onAppear() {
                recordsArr = viewModel.userCore.readFile().map(\.toInt)
                state = .menu
                viewModel.userCore.isAlive = true
            }
    }
}
